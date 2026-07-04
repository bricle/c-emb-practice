#include "ring_buffer.h"

#include <assert.h>
#include <stdio.h>

uint8_t buffer[BUFFER_SIZE];
int main(void)
{
    ring_buffer_t rb;
    uint8_t value = 0U;
    uint16_t i;

    rb_init(&rb, BUFFER_SIZE, buffer);
    assert(rb_get_len(&rb) == 0);
    assert(rb_get_space(&rb) == BUFFER_SIZE - 1);
    assert(rb_is_empty(&rb));
    assert(!rb_is_full(&rb));
    assert(rb_get(&rb, &value) == 0);

    for (i = 0U; i < BUFFER_SIZE - 1U; ++i)
    {
        assert(rb_put(&rb, (uint8_t)i) == 1);
    }
    assert(rb_get_space(&rb) == 0);
    assert(rb_get_len(&rb) == (BUFFER_SIZE - 1U));
    assert(rb_is_full(&rb));
    assert(rb_put(&rb, 0xFFU) == 0);

    for (i = 0U; i < 8U; ++i)
    {
        assert(rb_get(&rb, &value) == 1);
        assert(value == (uint8_t)i);
        assert(rb_get_len(&rb) == (BUFFER_SIZE - 2U - i));
        assert(rb_get_space(&rb) == (1U + i));
    }
    for (i = 0U; i < 8U; ++i)
    {
        assert(rb_put(&rb, (uint8_t)(BUFFER_SIZE + i)) == 1);
    }
    /* head 已从缓冲区末尾回环，此时队列应再次处于满状态。 */
    assert(rb_is_full(&rb));
    assert(rb_get_len(&rb) == (BUFFER_SIZE - 1U));
    assert(rb_get_space(&rb) == 0U);

    for (i = 8U; i < BUFFER_SIZE - 1U; ++i)
    {
        assert(rb_get(&rb, &value) == 1);
        assert(value == (uint8_t)i);
        assert(rb_get_len(&rb) == (BUFFER_SIZE + 6U - i));
        assert(rb_get_space(&rb) == (i - 7U));
    }
    for (i = 0U; i < 8U; ++i)
    {
        assert(rb_get(&rb, &value) == 1);
        assert(value == (uint8_t)(BUFFER_SIZE + i));
        assert(rb_get_len(&rb) == (7U - i));
        assert(rb_get_space(&rb) == (8U + i));
    }

    assert(rb_is_empty(&rb));
    assert(!rb_is_full(&rb));
    assert(rb_get_len(&rb) == 0U);
    assert(rb_get_space(&rb) == (BUFFER_SIZE - 1U));
    assert(rb_get(&rb, &value) == 0);
    puts("ring_buffer tests passed");
    return 0;
}
