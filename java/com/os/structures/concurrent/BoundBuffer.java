package com.os.structures.concurrent;

import java.util.List;
import java.util.Optional;

public interface BoundBuffer<ValueType> {
    void add(ValueType value) throws InterruptedException;
    ValueType remove() throws InterruptedException;
    Optional<ValueType> tryRemove();
}