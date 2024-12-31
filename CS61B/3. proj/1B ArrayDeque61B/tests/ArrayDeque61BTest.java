package tests;

import jh61b.utils.Reflection;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import java.lang.reflect.Field;
import java.util.List;

import static com.google.common.truth.Truth.assertThat;
import static com.google.common.truth.Truth.assertWithMessage;

import src.ArrayDeque61B;
import src.Deque61B;
import src.LinkedListDeque61B;

public class ArrayDeque61BTest {

    @Test
    @DisplayName("ArrayDeque61B has no fields besides backing array and primitives")
    void noNonTrivialFields() {
        List<Field> badFields = Reflection.getFields(ArrayDeque61B.class)
                .filter(f -> !(f.getType().isPrimitive() || f.getType().equals(Object[].class) || f.isSynthetic()))
                .toList();

        assertWithMessage("Found fields that are not array or primitives").that(badFields).isEmpty();
    }

    //test Get
    @Test
    public void testGet() {
        // 创建一个 ArrayDeque 实例并添加一些元素
        ArrayDeque61B<Integer> deque = new ArrayDeque61B<>();
        deque.addLast(10);
        deque.addLast(20);
        deque.addLast(30);

        // 测试有效的索引
        assertThat(deque.get(0)).isEqualTo(10);  // 第一个元素应该是 10
        assertThat(deque.get(1)).isEqualTo(20);  // 第二个元素应该是 20
        assertThat(deque.get(2)).isEqualTo(30);  // 第三个元素应该是 30

        // 测试无效的索引
        assertThat(deque.get(-1)).isNull();  // 负索引应该返回 null
        assertThat(deque.get(3)).isNull();  // 超出范围的索引应该返回 null
    }

    @Test
    public void testIsEmpty() {
        ArrayDeque61B<Integer> deque = new ArrayDeque61B<>();
        // 检查 deque 是否为空，期望是空的
        assertThat(deque.isEmpty()).isTrue();

        // 添加一个元素后，deque 不应该为空
        deque.addLast(10);
        assertThat(deque.isEmpty()).isFalse();
    }

    @Test
    public void testSize() {
        ArrayDeque61B<Integer> deque = new ArrayDeque61B<>();
        // 检查初始大小，应该是 0
        assertThat(deque.size()).isEqualTo(0);

        // 添加元素后，大小应该变化
        deque.addLast(10);
        assertThat(deque.size()).isEqualTo(1);

        deque.addLast(20);
        assertThat(deque.size()).isEqualTo(2);
    }

    @Test
    public void testToList() {
        ArrayDeque61B<Integer> deque = new ArrayDeque61B<>();

        // 测试空队列
        List<Integer> emptyList = deque.toList();
        assertThat(emptyList).isEmpty();  // 空队列应该返回一个空的 List

        // 添加元素
        deque.addLast(10);
        deque.addLast(20);
        deque.addLast(30);

        // 测试非空队列
        List<Integer> list = deque.toList();
        assertThat(list).hasSize(3);  // List 应该有 3 个元素
        assertThat(list).containsExactly(10, 20, 30);  // List 中的元素应与队列顺序一致
    }

    @Test
    public void testRemoveFirst() {
        ArrayDeque61B<Integer> deque = new ArrayDeque61B<>();

        deque.addLast(10);
        deque.addLast(20);
        deque.addLast(30);

        // Ensure the size is 3 after adding
        assertThat(deque.size()).isEqualTo(3);

        // Remove first element
        Integer removed = deque.removeFirst();

        // Ensure the correct item is removed (10)
        assertThat(removed).isEqualTo(10);

        // Ensure the size decreases by 1
        assertThat(deque.size()).isEqualTo(2);

        // Ensure the new first element is correct
        assertThat(deque.get(0)).isEqualTo(20);
    }

    @Test
    public void testRemoveLast() {
        ArrayDeque61B<Integer> deque = new ArrayDeque61B<>();

        deque.addLast(10);
        deque.addLast(20);
        deque.addLast(30);

        // Ensure the size is 3 after adding
        assertThat(deque.size()).isEqualTo(3);

        // Remove last element
        Integer removed = deque.removeLast();

        // Ensure the correct item is removed (30)
        assertThat(removed).isEqualTo(30);

        // Ensure the size decreases by 1
        assertThat(deque.size()).isEqualTo(2);

        // Ensure the new last element is correct
        assertThat(deque.get(deque.size() - 1)).isEqualTo(20);
    }

    @Test
    public void testEdgeCases() {
        ArrayDeque61B<Integer> deque = new ArrayDeque61B<>();

        // Remove from empty deque
        assertThat(deque.removeFirst()).isNull();
        assertThat(deque.removeLast()).isNull();

        // Add and remove in sequence
        deque.addFirst(1);
        deque.addFirst(2);
        deque.addFirst(3);

        assertThat(deque.removeLast()).isEqualTo(1);
        assertThat(deque.removeFirst()).isEqualTo(3);
        assertThat(deque.size()).isEqualTo(1);

        // Remove all
        deque.removeFirst();
        assertThat(deque.isEmpty()).isTrue();
    }

    @Test
    public void testEqualDeques61B() {
        Deque61B<String> lld1 = new LinkedListDeque61B<>();
        Deque61B<String> lld2 = new LinkedListDeque61B<>();

        lld1.addLast("front");
        lld1.addLast("middle");
        lld1.addLast("back");

        lld2.addLast("front");
        lld2.addLast("middle");
        lld2.addLast("back");

        assertThat(lld1).isEqualTo(lld2);
    }

    @Test
    public void test混合添加移除() {
        ArrayDeque61B<Integer> deque = new ArrayDeque61B<>();
        deque.addLast(1);
        deque.addFirst(2);
        deque.addLast(3);
        deque.removeFirst();
        deque.addFirst(4);
        assertThat(deque.toList()).containsExactly(4, 1, 3);
    }

    @Test
    public void testGetRecursive() {
        ArrayDeque61B<Integer> deque = new ArrayDeque61B<>();
        deque.addLast(10);
        deque.addLast(20);
        deque.addLast(30);
        assertThat(deque.getRecursive(0)).isEqualTo(10);
        assertThat(deque.getRecursive(1)).isEqualTo(20);
        assertThat(deque.getRecursive(2)).isEqualTo(30);
        assertThat(deque.getRecursive(-1)).isNull();
        assertThat(deque.getRecursive(3)).isNull();
    }

    @Test
    public void testEqualsWithNull() {
        ArrayDeque61B<Object> deque1 = new ArrayDeque61B<>();
        deque1.addLast(null);
        deque1.addLast("a");

        ArrayDeque61B<Object> deque2 = new ArrayDeque61B<>();
        deque2.addLast("a");
        deque2.addFirst(null);

        assertThat(deque1.equals(deque2)).isTrue();
    }

    @Test
    public void testEqualsDifferentTypes() {
        ArrayDeque61B<String> deque1 = new ArrayDeque61B<>();
        deque1.addLast("a");

        LinkedListDeque61B<String> deque2 = new LinkedListDeque61B<>();
        deque2.addLast("a");

        assertThat(deque1.equals(deque2)).isFalse();
    }

    @Test
    public void testExtremeSize() {
        ArrayDeque61B<Integer> deque = new ArrayDeque61B<>();
        int maxSize = 1000000;
        for (int i = 0; i < maxSize; i++) {
            deque.addLast(i);
        }
        assertThat(deque.size()).isEqualTo(maxSize);
        assertThat(deque.removeFirst()).isEqualTo(0);
        assertThat(deque.size()).isEqualTo(maxSize - 1);
        assertThat(deque.removeLast()).isEqualTo(maxSize - 1);
        assertThat(deque.size()).isEqualTo(maxSize - 2);
    }

    @Test
    public void test边界条件() {
        ArrayDeque61B<Integer> deque = new ArrayDeque61B<>();
        assertThat(deque.isEmpty()).isTrue();
        assertThat(deque.size()).isEqualTo(0);
        assertThat(deque.removeFirst()).isNull();
        assertThat(deque.removeLast()).isNull();
        deque.addFirst(1);
        assertThat(deque.size()).isEqualTo(1);
        assertThat(deque.get(0)).isEqualTo(1);
        deque.removeFirst();
        assertThat(deque.isEmpty()).isTrue();
    }


}
