#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdbool.h>
#include <stdint.h>

#define BUFFER_SIZE 16

typedef struct
{
    uint8_t *buf;
    uint16_t head;
    // 头指针，写指针，指向的是待写的地址，而不是最前面已写的地址
    // 头指针指向的地址永远是空的（空一格的方案）
    // 头指针指向的地址除了满了的时候不是空的，其余情况都是空的（不空格的方案）

    uint16_t tail;
    // 尾指针，读指针，指向的是待读的指针,这个地址已经可以读了

    uint16_t size;
    // 缓冲区的大小，单位是字节，总长度，包括一个无法使用的字节
}ring_buffer_t;

// 采用空一个格子的方案

// 接口
// 初始化
void rb_init(ring_buffer_t *rb, uint16_t size, uint8_t *buf);

// 是否满
bool rb_is_full(ring_buffer_t *rb);

// 是否空
bool rb_is_empty(ring_buffer_t *rb);

// 获取当前已有的有效字节数量
uint16_t rb_get_len(ring_buffer_t *rb);

// 获取当前剩余可写入的字节数
uint16_t rb_get_space(ring_buffer_t *rb);
// 压入一个字节
int rb_put(ring_buffer_t *rb, uint8_t ch);
// 取出一个字节
int rb_get(ring_buffer_t *rb, uint8_t *ch);
// 偷看基于当前读指针某个offset的字节

// 丢弃指定长度的字节

#endif
