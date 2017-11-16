#include <zstring.h>

class IMDLBinaryFile;
class UiState;

// Maybe remove when we really don't care about mdl logging anymore
void Write(IMDLBinaryFile* pmdlFile, const UiState& value);
ZString GetString(int indent, const UiState& value);
ZString GetFunctionName(const UiState& value);

#pragma once

#include "model.h"

#include <any>
#include <functional>
#include <list>


class UiObjectContainer : public IObject {

private:
    std::map<std::string, std::any> m_map;

public:
    UiObjectContainer(const std::map<std::string, std::any> &map) :
        m_map(map)
    {
    }

    template <typename Type>
    Type Get(const std::string &key) {
        auto found = m_map.find(key);
        if (found == m_map.end()) {
            throw std::runtime_error("Key not found: " + key);
        }

        try
        {
            return std::any_cast<Type>(found->second);
        }
        catch (const std::bad_any_cast &)
        {
            throw std::runtime_error("Key found but not of valid type: " + key);
        }
    }

    TRef<StringValue> GetString(const std::string &key) {
        return Get<TRef<StringValue>>(key);
    }

    TRef<Boolean> GetBoolean(const std::string &key) {
        return Get<TRef<Boolean>>(key);
    }

    TRef<Number> GetNumber(const std::string &key) {
        return Get<TRef<Number>>(key);
    }

};


// Maybe remove when we really don't care about mdl logging anymore
class ModifiableUiStateName {
public:
    static ZString GetName() { return "ModifiableState"; }
};

class UiState : public UiObjectContainer {

private:
    std::string m_name;
public:
    UiState(const std::string &name, const std::map<std::string, std::any> &map = {}) :
        UiObjectContainer(map),
        m_name(name)
    {}

    std::string GetName() const {
        return m_name;
    }

    template <class T>
    T* as() const {
        //const T* result = dynamic_cast<const T*>(this);
        //if (!result) {
        //    throw std::runtime_error("Not in the correct state");
        //}
        return (T*)this;
    }
};

class SimpleUiState : public UiState {
public:
    SimpleUiState(const std::string &name, const std::map<std::string, std::any> &map = {}) :
        UiState(name, map)
    {
    }
};


typedef TStaticValue<UiState> UiStateValue;
typedef TModifiableValue<UiState, ModifiableUiStateName> UiStateModifiableValue;

template <typename EntryType>
class UiList : public Value {
private:
    std::list<EntryType> m_list;

protected:
    std::list<EntryType>& GetListInternal() {
        return m_list;
    }

public:
    template<class... T>
    UiList(const std::list<EntryType> &list, T ... values) :
        m_list(list),
        Value(values...)
    {}

    const std::list<EntryType>& GetList() {
        return m_list;
    }

    void Insert(int position, EntryType entry) {
        auto iterator = m_list.begin();
        std::advance(iterator, position);

        m_list.insert(iterator, entry);
        Changed();
    }

    void InsertAtEnd(EntryType entry) {
        m_list.insert(m_list.end(), entry);
        Changed();
    }

    void Remove(int position) {
        auto iterator = m_list.begin();
        std::advance(iterator, position);

        m_list.erase(iterator);
        Changed();
    }

    void RemoveAll() {
        m_list.clear();
        Changed();
    }
};

typedef UiList<TRef<UiObjectContainer>> ContainerList;
typedef UiList<TRef<Image>> ImageList;


template <typename ResultEntryType, typename OriginalEntryType>
class MappedList : public UiList<ResultEntryType> {
private:
    std::function<ResultEntryType(OriginalEntryType, TRef<Number>)> m_callback;

public:
    MappedList(const TRef<UiList<OriginalEntryType>>& list, std::function<ResultEntryType(OriginalEntryType, TRef<Number>)> callback) :
        UiList<ResultEntryType>({}, list),
        m_callback(callback)
    {
    }

    TRef<UiList<OriginalEntryType>> GetSourceList() {
        auto child = UiList<ResultEntryType>::GetChild(0);
        return (TRef<UiList<OriginalEntryType>>)(UiList<OriginalEntryType>*)child;
    }

    void Evaluate() override {
        std::list<ResultEntryType> list;
        int i = 0;
        for (auto entry : GetSourceList()->GetList()) {
            TRef<Number> index = new Number((float)i);

            list.push_back(m_callback(entry, index));
            ++i;
        }

        UiList<ResultEntryType>::GetListInternal() = list;
    }
};
