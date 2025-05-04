#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>


/**
 * @brief 环形缓冲区结构体
 */
typedef struct {
    unsigned char* buffer;   // 缓冲区数据指针
    unsigned int size;      // 缓冲区总大小
    unsigned int head;      // 读指针位置
    unsigned int tail;      // 写指针位置
    bool full;              // 缓冲区是否已满标志
} RingBuffer;

/**
 * @brief 初始化环形缓冲区
 * @param size 缓冲区大小
 */
RingBuffer* RingBuffer_Init(unsigned int size);

/**
 * @brief 向环形缓冲区写入一个字节
 * @param rb 环形缓冲区结构体指针
 * @param data 要写入的数据
 * @return 写入成功返回true，失败返回false
 */
bool RingBuffer_Write(RingBuffer* rb, unsigned char data);

/**
 * @brief 向环形缓冲区写入多个字节
 * @param rb 环形缓冲区结构体指针
 * @param data 要写入的数据指针
 * @param length 要写入的数据长度
 * @return 实际写入的字节数
 */
unsigned int RingBuffer_WriteMultiple(RingBuffer* rb, const unsigned char* data, unsigned int length);

/**
 * @brief 从环形缓冲区读取一个字节
 * @param rb 环形缓冲区结构体指针
 * @param data 读取数据的存放位置
 * @return 读取成功返回true，失败（缓冲区为空）返回false
 */
bool RingBuffer_Read(RingBuffer* rb, unsigned char* data);

/**
 * @brief 从环形缓冲区读取多个字节
 * @param rb 环形缓冲区结构体指针
 * @param data 读取数据的存放指针
 * @param length 期望读取的最大长度
 * @return 实际读取的字节数
 */
unsigned int RingBuffer_ReadMultiple(RingBuffer* rb, unsigned char* data, unsigned int length);

/**
 * @brief 查看环形缓冲区是否为空
 * @param rb 环形缓冲区结构体指针
 * @return 缓冲区为空返回true，否则返回false
 */
bool RingBuffer_IsEmpty(const RingBuffer* rb);

/**
 * @brief 查看环形缓冲区是否已满
 * @param rb 环形缓冲区结构体指针
 * @return 缓冲区已满返回true，否则返回false
 */
bool RingBuffer_IsFull(const RingBuffer* rb);

/**
 * @brief 获取环形缓冲区中当前的数据量
 * @param rb 环形缓冲区结构体指针
 * @return 当前已使用的字节数
 */
unsigned int RingBuffer_GetCount(const RingBuffer* rb);

/**
 * @brief 获取环形缓冲区中当前的剩余空间
 * @param rb 环形缓冲区结构体指针
 * @return 当前还可写入的字节数
 */
unsigned int RingBuffer_GetFree(const RingBuffer* rb);


/**
 * @brief 释放环形缓冲区资源
 * @param rb 环形缓冲区结构体指针
 */
void RingBuffer_Destroy(RingBuffer* rb);

#endif /* RINGBUFFER_H */
