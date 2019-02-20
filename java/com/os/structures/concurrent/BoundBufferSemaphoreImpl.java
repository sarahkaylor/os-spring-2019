package com.os.structures.concurrent;

import java.util.ArrayDeque;
import java.util.Optional;
import java.util.Queue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.ReentrantLock;

public class BoundBufferSemaphoreImpl<ValueType> implements BoundBuffer<ValueType> {
    private final Queue<ValueType> queue = new ArrayDeque<>(5);
    private final Semaphore freeSpace = new Semaphore(5);
    private final Semaphore usedSpace = new Semaphore(0);
    //private final ReentrantLock mutex = new ReentrantLock(false);
    private final Semaphore mutex = new Semaphore(1);

    @Override
    public void add(ValueType value) throws InterruptedException {
        freeSpace.acquire(1);
        mutex.acquire();
        queue.add(value);
        mutex.release();
        usedSpace.release(1);
    }

    @Override
    public ValueType remove() throws InterruptedException {
        usedSpace.acquire(1);
        mutex.acquire();
        ValueType value = queue.remove();
        mutex.release();
        freeSpace.release(1);
        return value;
    }

    @Override
    public Optional<ValueType> tryRemove() {
        return Optional.empty();
    }
}
