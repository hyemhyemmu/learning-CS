#include "RingBuffer.h"

RingBuffer* RingBuffer_Init(unsigned int size){
    RingBuffer *newRingBuffer = (RingBuffer *)malloc(sizeof(RingBuffer));
    if (!newRingBuffer){
        fprintf(stderr, "Out of memory.\n");
        errno = ENOMEM;
        return NULL;
    }

    newRingBuffer->head = 0;
    newRingBuffer->tail = 0;
    newRingBuffer->size = size;
    newRingBuffer->full = false;
    newRingBuffer->buffer = (char *)malloc(sizeof(char) * size);
    return newRingBuffer;
}

void RingBuffer_Destroy(RingBuffer *rb){
    if (rb == NULL){
        fprintf(stderr, "The buffer is invalid.\n");
        return;
    }
    free(rb->buffer);
    free(rb);
}

bool RingBuffer_Write(RingBuffer* rb, unsigned char data){
    if (rb == NULL){
        fprintf(stderr, "The buffer is invalid.\n");
        return false;
    }
    
    if (rb->full){
        rb->buffer[rb->tail] = data;
        rb->tail = (rb->tail + 1) % rb->size; // 考虑环形缓冲区循环
        rb->head = rb->tail; // 头指针跟随尾指针移动
    } else {
        rb->buffer[rb->tail] = data;
        rb->tail = (rb->tail + 1) % rb->size;
        
        // 检查缓冲区是否已满
        if (rb->tail == rb->head){
            rb->full = true;
        }
    }
    
    return true;
}

// 写入多个字节本质上是通过循环调用写入一个字节的函数
unsigned int RingBuffer_WriteMultiple(RingBuffer* rb, const unsigned char* data, unsigned int length){
    for (int i = 0; i < length;i++){
        RingBuffer_Write(rb, data[i]);
    }
    return length;
}

bool RingBuffer_Read(RingBuffer* rb, unsigned char* data){
    if (rb == NULL || data == NULL){
        fprintf(stderr, "Invalid buffer or data pointer.\n");
        return false;
    }
    
    // 检查缓冲区是否为空
    if (rb->head == rb->tail && !rb->full){
        return false;  
    }
    
    // 从头指针位置读取数据
    *data = rb->buffer[rb->head];
    rb->head = (rb->head + 1) % rb->size;  // 更新头指针
    rb->full = false;  // 读取后缓冲区一定不满
    
    return true;
}

unsigned int RingBuffer_ReadMultiple(RingBuffer* rb, unsigned char* data, unsigned int length){
    if (rb == NULL || data == NULL){
        fprintf(stderr, "Invalid buffer or data pointer.\n");
        return 0;
    }
    
    unsigned int count = 0;
    for (unsigned int i = 0; i < length; i++){
        if (RingBuffer_Read(rb, &data[i])){
            count++;
        } else {
            break;  // 缓冲区已空，停止读取
        }
    }
    
    return count;
}

unsigned int RingBuffer_GetCount(const RingBuffer* rb){
    if (rb == NULL){
        fprintf(stderr, "Invalid buffer.\n");
        return 0;
    }
    
    if (rb->full){
        return rb->size;
    }
    
    if (rb->tail >= rb->head){
        return rb->tail - rb->head;
    } else {
        return rb->size - (rb->head - rb->tail); // 绕一圈
    }
}

unsigned int RingBuffer_GetFree(const RingBuffer* rb){
    if (rb == NULL){
        fprintf(stderr, "Invalid buffer.\n");
        return 0;
    }
    
    return rb->size - RingBuffer_GetCount(rb);
}

bool RingBuffer_IsEmpty(const RingBuffer* rb){
    if (rb == NULL){
        fprintf(stderr, "Invalid buffer.\n");
        return true;
    }

    return (rb->head == rb->tail && !rb->full);
}

bool RingBuffer_IsFull(const RingBuffer* rb){
    if (rb == NULL){
        fprintf(stderr, "Invalid buffer.\n");
        return false;
    }

    return rb->full;
}
