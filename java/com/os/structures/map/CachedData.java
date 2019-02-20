package com.os.structures.map;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class CachedData {
    private final ReadWriteLock lock = new ReentrantReadWriteLock(false);
    private final Map<String, Long> data = new HashMap<>();

    Long getValue(String text) {
        try {
            lock.readLock().lock();
            Long value = data.getOrDefault(text, null);
            if(value != null) {
                return value;
            }
        } finally {
            lock.readLock().unlock();
        }
        Long newValue = calculateValue(text);
        try {
            lock.writeLock().lock();
            if(!data.containsKey(text)) {
                data.put(text, newValue);
            }
            return newValue;
        } finally {
            lock.writeLock().unlock();
        }
    }

    Long calculateValue(String text) {
        long count = 0;
        for(int i = 0; i < text.length(); i++) {
            count += (int)text.charAt(i);
        }
        return count;
    }
}
