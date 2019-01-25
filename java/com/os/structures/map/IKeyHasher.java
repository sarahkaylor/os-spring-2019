package com.os.structures.map;

/**
 * A contract that describes how to hash a key and compare two keys.
 * @param <KeyType> the type of the key
 */
public interface IKeyHasher<KeyType> {
    /**
     * returns an integer hash value for the provided {@code key}
     */
    int getHash(KeyType key);

    /**
     * determines if two keys are equivalent
     */
    boolean keysAreEqual(KeyType a, KeyType b);
}
