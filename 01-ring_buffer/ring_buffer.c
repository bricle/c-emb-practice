#include "ring_buffer.h"

#include <string.h>
// todo (head + 1) % size == tail
// 初始化里面检查输入参数
void rb_init(ring_buffer_t *rb, uint16_t size, uint8_t *buf)
{
    if (buf == NULL) {
        return;
    }
    rb->head = 0;
    rb->tail = 0;
    rb->size = size;
    rb->buf = buf;
    memset(rb->buf, 0, size);
}

bool rb_is_full(ring_buffer_t *rb)
{
    if ((rb->head + 1) == rb->tail) {
        return true;
    }
    if ((rb->head + 1) >= rb->size)
    {
        if (rb->tail == 0) {
            return true;
        }
    }
    return false;
}

bool rb_is_empty(ring_buffer_t *rb)
{
    return rb->head == rb->tail;
}

int rb_put(ring_buffer_t *rb, uint8_t ch)
{
    if (rb_is_full(rb)) {
        return 0;
    }
    rb->buf[rb->head] = ch;
    rb->head++;
    if (rb->head >= rb->size)
    {
        rb->head = 0;
    }
    return 1;
}

int rb_get(ring_buffer_t *rb, uint8_t *ch)
{
    if (rb_is_empty(rb) == true) {
        return 0;
    }
    *ch = rb->buf[rb->tail];
    rb->tail++;
    if (rb->tail >= rb->size)
    {
        rb->tail = 0;
    }
    return 1;
}

uint16_t rb_get_len(ring_buffer_t *rb)
{
    // 没有回环
    if (rb-> head >= rb -> tail) {
        return rb->head - rb->tail;
    }
    // 有回环
    // 先把head加上size，即环形转直线，再减去tail，得到的就是有效字节数
    return rb->size + rb->head - rb->tail;
}

uint16_t rb_get_space(ring_buffer_t *rb)
{
    return rb->size - 1U - rb_get_len(rb);
}
