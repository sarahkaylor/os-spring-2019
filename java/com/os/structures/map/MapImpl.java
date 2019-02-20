package com.os.structures.map;

import java.util.ArrayList;
import java.util.List;
import java.util.ListIterator;
import java.util.Optional;
import java.util.function.BiFunction;
import java.util.function.Function;

public class MapImpl<KeyType, ValueType> implements IMap<KeyType, ValueType> {
    private final IKeyHasher<KeyType> keyHasher;


    private int size;
    private final ArrayList<Entry<KeyType, ValueType>>[] entries;
    private static final int DEFAULT_CAPACITY = 10000;

    private static final class Entry<KeyType, ValueType> {
        final KeyType key;
        final ValueType value;

        Entry(KeyType key, ValueType value) {
            this.key = key;
            this.value = value;
        }
    }

    public MapImpl(IKeyHasher<KeyType> keyHasher) {
        this(keyHasher, DEFAULT_CAPACITY);
    }

    public MapImpl(IKeyHasher<KeyType> keyHasher, int capacity) {
        this.keyHasher = keyHasher;
        this.entries = createArray(capacity);
        this.size = 0;
    }

    // this is separated into a function to deal with the Java compiler warning about
    // creating arrays of generic types.
    private static <KeyType,ValueType> ArrayList<Entry<KeyType,ValueType>>[] createArray(int size) {
        @SuppressWarnings("unchecked")
        ArrayList<Entry<KeyType, ValueType>>[] array =
            (ArrayList<Entry<KeyType,ValueType>>[])new ArrayList<?>[size];
        return array;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public void put(KeyType key, ValueType value) {
        int index = findEntriesIndex(key);
        if(entries[index] == null) {
            entries[index] = new ArrayList<>();
        }
        int foundIndex = findListIndex(entries[index], key);
        if(foundIndex >= 0) {
            entries[index].remove(foundIndex);
        } else {
            ++size;
        }
        entries[index].add(new Entry<>(key, value));
    }

    @Override
    public Optional<ValueType> get(KeyType key) {
        int index = findEntriesIndex(key);
        if(entries[index] == null) {
            return Optional.empty();
        }
        int foundIndex = findListIndex(entries[index], key);
        if(foundIndex < 0) {
            return Optional.empty();
        }
        return Optional.of(entries[index].get(foundIndex).value);
    }

    @Override
    public boolean remove(KeyType key) {
        int index = findEntriesIndex(key);
        if(entries[index] == null) {
            return false;
        }
        int foundIndex = findListIndex(entries[index], key);
        if(foundIndex < 0) {
            return false;
        }
        entries[index].remove(foundIndex);
        --size;
        return true;
    }

    private int findEntriesIndex(KeyType key) {
        int hash = keyHasher.getHash(key);
        return hash % entries.length;
    }

    private int findListIndex(List<Entry<KeyType, ValueType>> list, KeyType key) {
        ListIterator<Entry<KeyType, ValueType>> iterator = list.listIterator();
        while (iterator.hasNext()) {
            Entry<KeyType, ValueType> entry = iterator.next();
            if(keyHasher.keysAreEqual(entry.key, key)) {
                return iterator.previousIndex();
            }
        }
        return -1;
    }
}
