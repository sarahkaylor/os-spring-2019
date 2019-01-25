package com.os.structures.map;

import java.util.Optional;

/**
 * A simple java-typical map contract.
 * @param <KeyType> the type of the key in the map
 * @param <ValueType> the type of the value in the map
 */
public interface IMap<KeyType, ValueType> {
    int size();
    void put(KeyType key, ValueType value);
    Optional<ValueType> get(KeyType key);
    boolean remove(KeyType key);
}
