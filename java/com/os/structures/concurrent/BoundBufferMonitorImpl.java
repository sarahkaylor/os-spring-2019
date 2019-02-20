package com.os.structures.concurrent;

import java.util.ArrayDeque;
import java.util.Optional;
import java.util.Queue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.ReentrantLock;

public class BoundBufferMonitorImpl<ValueType> implements BoundBuffer<ValueType> {
    private final Queue<ValueType> queue = new ArrayDeque<>(5);

    @Override
    public void add(ValueType value) throws InterruptedException {
        synchronized (queue) {
            while(queue.size() >= 5) {
                queue.wait();
            }
            queue.add(value);
            queue.notify();
        }
    }

    @Override
    public ValueType remove() throws InterruptedException {
        synchronized (queue) {
            while(queue.size() == 0) {
                queue.wait();
            }
            ValueType value = queue.remove();
            queue.notify();
            return value;
        }
    }

    @Override
    public Optional<ValueType> tryRemove() {
        return Optional.empty();
    }
}
