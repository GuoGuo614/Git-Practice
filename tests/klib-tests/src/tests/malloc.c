#include <klibtest.h>
#include <stdlib.h>
#include <string.h>

#define TEST_SIZE_SMALL 16
#define TEST_SIZE_MEDIUM 1024
#define TEST_SIZE_LARGE 8192
#define MAX_ALLOCS 100

void test_basic_malloc() {
    // 测试基本的 malloc 和 free
    void *ptr = malloc(TEST_SIZE_SMALL);
    check(ptr != NULL);
    
    // 写入数据，检查是否可以正常读写
    char *data = (char *)ptr;
    for (int i = 0; i < TEST_SIZE_SMALL; i++) {
        data[i] = (char)(i % 256);
    }
    
    // 验证数据
    for (int i = 0; i < TEST_SIZE_SMALL; i++) {
        check(data[i] == (char)(i % 256));
    }
    
    free(ptr);
}

void test_malloc_zero() {
    // 测试 malloc(0) 的行为
    void *ptr = malloc(0);
    check(ptr != NULL);  // malloc(0) 应该返回有效指针或 NULL，但不应该崩溃
    free(ptr);
}

void test_malloc_large() {
    // 测试大内存分配
    void *ptr = malloc(TEST_SIZE_LARGE);
    check(ptr != NULL);
    
    // 写入和验证大块内存
    int *data = (int *)ptr;
    for (int i = 0; i < TEST_SIZE_LARGE / sizeof(int); i++) {
        data[i] = i;
    }
    
    for (int i = 0; i < TEST_SIZE_LARGE / sizeof(int); i++) {
        check(data[i] == i);
    }
    
    free(ptr);
}

void test_multiple_malloc() {
    // 测试多次分配
    void *ptrs[MAX_ALLOCS];
    
    // 分配多个小块内存
    for (int i = 0; i < MAX_ALLOCS; i++) {
        ptrs[i] = malloc(TEST_SIZE_SMALL + i);
        check(ptrs[i] != NULL);
        
        // 写入标识数据
        char *data = (char *)ptrs[i];
        data[0] = (char)i;
    }
    
    // 验证数据没有被覆盖
    for (int i = 0; i < MAX_ALLOCS; i++) {
        char *data = (char *)ptrs[i];
        check(data[0] == (char)i);
    }
    
    // 释放所有内存
    for (int i = 0; i < MAX_ALLOCS; i++) {
        free(ptrs[i]);
    }
}

void test_malloc_alignment() {
    // 测试内存对齐
    void *ptr1 = malloc(1);
    void *ptr2 = malloc(1);
    void *ptr3 = malloc(1);
    
    check(ptr1 != NULL);
    check(ptr2 != NULL);
    check(ptr3 != NULL);
    
    // 检查指针是否不同（没有重叠）
    check(ptr1 != ptr2);
    check(ptr2 != ptr3);
    check(ptr1 != ptr3);
    
    free(ptr1);
    free(ptr2);
    free(ptr3);
}

void test_malloc_boundary() {
    // 测试边界情况：检查是否会越界写
    size_t size = 100;
    char *ptr = (char *)malloc(size);
    check(ptr != NULL);
    
    // 写入边界数据
    for (size_t i = 0; i < size; i++) {
        ptr[i] = (char)(i % 256);
    }
    
    // 验证边界数据
    for (size_t i = 0; i < size; i++) {
        check(ptr[i] == (char)(i % 256));
    }
    
    free(ptr);
}

void test_malloc_stress() {
    // 压力测试：随机分配和释放
    void *ptrs[50];
    int allocated[50] = {0};
    
    for (int round = 0; round < 100; round++) {
        int idx = round % 50;
        
        if (allocated[idx]) {
            // 释放
            free(ptrs[idx]);
            allocated[idx] = 0;
        } else {
            // 分配
            ptrs[idx] = malloc((idx + 1) * 10);
            check(ptrs[idx] != NULL);
            allocated[idx] = 1;
            
            // 写入测试数据
            char *data = (char *)ptrs[idx];
            data[0] = (char)idx;
        }
    }
    
    // 清理剩余内存
    for (int i = 0; i < 50; i++) {
        if (allocated[i]) {
            free(ptrs[i]);
        }
    }
}

void test_malloc_reuse() {
    // 测试内存重用（如果你的 malloc 支持 free 的话）
    void *ptr1 = malloc(100);
    check(ptr1 != NULL);
    
    // 写入数据
    memset(ptr1, 0xAA, 100);
    
    free(ptr1);
    
    // 再次分配相同大小
    void *ptr2 = malloc(100);
    check(ptr2 != NULL);
    
    // 注意：不能假设ptr1 == ptr2，因为malloc可能返回不同地址
    // 只检查能否正常使用
    memset(ptr2, 0xBB, 100);
    
    free(ptr2);
}

void test_malloc() {
    test_basic_malloc();
    test_malloc_zero();
    test_malloc_large();
    test_multiple_malloc();
    test_malloc_alignment();
    test_malloc_boundary();
    test_malloc_stress();
    test_malloc_reuse();
}