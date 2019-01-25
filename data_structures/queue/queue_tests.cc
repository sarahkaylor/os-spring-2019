#include "data_structures/queue/queue.h"
#include "gtest/gtest.h"

using data_structures::Queue;

namespace data_structures {

TEST(QueueTests, testInitialStates) {

	Queue<std::string> queue;

	EXPECT_EQ(0, queue.size());
}

TEST(QueueTests, testAddOneThenRemoveOne) {

	Queue<std::string> queue;

	queue.addLast(std::string("hello world"));

	std::string value = queue.removeFirst();

	EXPECT_EQ(std::string("hello world"), value);
}

TEST(QueueTests, testAddFiveItemsThenRemoveThree) {

	Queue<std::string> queue;

	queue.addLast(std::string("hello world"));
	queue.addLast(std::string("abc"));
	queue.addLast(std::string("def"));
	queue.addLast(std::string("ghi"));
	queue.addLast(std::string("jkl"));

	EXPECT_EQ(5, queue.size());
	EXPECT_EQ(std::string("hello world"), queue.removeFirst());
	EXPECT_EQ(4, queue.size());
	EXPECT_EQ(std::string("abc"), queue.removeFirst());
	EXPECT_EQ(3, queue.size());
	EXPECT_EQ(std::string("def"), queue.removeFirst());
	EXPECT_EQ(2, queue.size());
}

TEST(QueueTests, testAddThenRemoveManyTimes) {
	Queue<std::string> queue;
	for(int i = 0; i < 20; i++) {
		queue.addLast(std::string("abc"));
		queue.addLast(std::string("def"));
		queue.addLast(std::string("ghi"));

		EXPECT_EQ(3, queue.size());
		EXPECT_EQ(std::string("abc"), queue.removeFirst());
		EXPECT_EQ(2, queue.size());
		EXPECT_EQ(std::string("def"), queue.removeFirst());
		EXPECT_EQ(1, queue.size());
		EXPECT_EQ(std::string("ghi"), queue.removeFirst());
		EXPECT_EQ(0, queue.size());
	}
}

} // namespace data_structures
