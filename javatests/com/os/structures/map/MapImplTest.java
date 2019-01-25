package com.os.structures.map;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

import java.util.Arrays;
import java.util.Collection;
import java.util.function.Supplier;

import static org.junit.Assert.*;

// this test can be run by this command:
// bazel test //javatests/com/os/structures/map:MapImplTest

// you can run all of the unit tests for a project with this command:
// bazel test //javatests/com/os/structures/...

// see https://github.com/junit-team/junit4/wiki/parameterized-tests for how parameterized tests work with JUnit-4
@RunWith(Parameterized.class)
public class MapImplTest {

    // The current factory method for our map;
    @Parameterized.Parameter(0)
    public Supplier<IMap<String, String>> createMapFn;

    // We run all of our tests with a good hash function, then
    // run all of our tests with a poor hash function
    @Parameterized.Parameters
    public static Collection<Object[]> getParameters() {
        Supplier<IMap<String,String>> mapWithGoodHash = MapImplTest::createMap;
        Supplier<IMap<String,String>> mapWithBadHash = MapImplTest::createBadMap;
        return Arrays.asList(
                new Object[]{mapWithGoodHash},
                new Object[]{mapWithBadHash}
        );
    }

    @Test
    public void testPutThenGet() {
        IMap<String,String> map = createMapFn.get();

        map.put("a", "abc");

        assertTrue(map.get("a").isPresent());
        assertEquals("abc", map.get("a").get());
    }

    @Test
    public void putTwiceOverwritesAndIncreasesSizeOnlyOnce() {
        IMap<String,String> map = createMapFn.get();

        map.put("a", "abc");

        assertEquals(1, map.size());
        assertTrue(map.get("a").isPresent());
        assertEquals("abc", map.get("a").get());

        map.put("a", "def");

        assertEquals(1, map.size());
        assertTrue(map.get("a").isPresent());
        assertEquals("def", map.get("a").get());
    }

    @Test
    public void testRemove() {
        IMap<String,String> map = createMapFn.get();
        assertEquals(0, map.size());
        assertFalse(map.remove("a"));

        map.put("a", "abc");

        assertEquals(1, map.size());

        assertTrue(map.remove("a"));

        assertEquals(0, map.size());

        assertFalse(map.remove("a"));
    }

    private static IMap<String, String> createMap() {
        return new MapImpl<>(new StringHasher());
    }

    private static IMap<String, String> createBadMap() {
        return new MapImpl<>(new BadStringHasher());
    }

    private static final class StringHasher implements IKeyHasher<String> {

        @Override
        public int getHash(String key) {
            return key.hashCode();
        }

        @Override
        public boolean keysAreEqual(String a, String b) {
            return a.equals(b);
        }
    }

    private static final class BadStringHasher implements IKeyHasher<String> {

        @Override
        public int getHash(String key) {
            return 0; // deliberately return the same key every time
        }

        @Override
        public boolean keysAreEqual(String a, String b) {
            return a.equals(b);
        }
    }
}
