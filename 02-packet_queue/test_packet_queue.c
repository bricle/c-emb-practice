#include "packet_queue.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
packet_queue_t pq;
packet_t test_pkt[PACKET_QUEUE_SIZE];
packet_t *temp_pkt;
int main(void)
{
    uint16_t i;
    printf("test start\r\n");
    assert(packet_queue_init(&pq) == 1);
    assert(packet_queue_is_empty(&pq));
    assert(!packet_queue_is_full(&pq));
    assert(0 == packet_queue_get_len(&pq));
    assert(PACKET_QUEUE_SIZE == packet_queue_get_space(&pq));
    assert(packet_queue_pop(&pq, &temp_pkt) == 0);
    for ( i = 0; i < 5; ++i)
    {
        test_pkt[i].len = 56 + i;
        test_pkt[i].type = 2 +i;
        assert(packet_queue_push(&pq, &test_pkt[i]) == 1);
    }
    assert(!packet_queue_is_empty(&pq));
    assert(!packet_queue_is_full(&pq));
    assert(i == packet_queue_get_len(&pq));
    assert((PACKET_QUEUE_SIZE - i) == packet_queue_get_space(&pq));

    for (i = 0; i < 3; ++i)
    {
        assert(packet_queue_pop(&pq, &temp_pkt) == 1);
        assert(temp_pkt == &test_pkt[i]);
    }
    assert(!packet_queue_is_empty(&pq));
    assert(!packet_queue_is_full(&pq));
    assert(2 == packet_queue_get_len(&pq));
    assert(6 == packet_queue_get_space(&pq));

    // 到这里的时候test_pkt[3] 和 test_pkt[4] 仍然在队列里，不能再修改以及push了
    // Caller must not modify or free pkt until it is popped back.
    uint16_t refill_idx[] = {0, 1, 2, 5, 6, 7};
    for (i = 0; i < 6; ++i)
    {
        uint16_t idx = refill_idx[i];

        test_pkt[idx].len = 56 + idx;
        test_pkt[idx].type = 2 + idx;

        assert(packet_queue_push(&pq, &test_pkt[idx]) == 1);
    }
    assert(!packet_queue_is_empty(&pq));
    assert(packet_queue_is_full(&pq));
    assert(8 == packet_queue_get_len(&pq));
    assert(0 == packet_queue_get_space(&pq));
    assert(packet_queue_push(&pq, &test_pkt[0]) == 0); // 满队列 push 失败

    for (i = 3; i < 5; ++i)
    {
        assert(packet_queue_pop(&pq, &temp_pkt) == 1);
        assert(temp_pkt == &test_pkt[i]);
    }
    assert(!packet_queue_is_empty(&pq));
    assert(!packet_queue_is_full(&pq));
    assert(6 == packet_queue_get_len(&pq));
    assert(2 == packet_queue_get_space(&pq));

    for (i = 0; i < 6; ++i)
    {
        uint16_t idx = refill_idx[i];
        assert(packet_queue_pop(&pq, &temp_pkt) == 1);
        assert(temp_pkt == &test_pkt[idx]);
    }
    assert(packet_queue_is_empty(&pq));
    assert(!packet_queue_is_full(&pq));
    assert(0 == packet_queue_get_len(&pq));
    assert(8 == packet_queue_get_space(&pq));
    return 0;
}
