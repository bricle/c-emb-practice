#include <stdbool.h>
#include "packet_queue.h"
#include <stdio.h>
#include <string.h>

int packet_queue_init(packet_queue_t *pq)
{
    if (pq == NULL) {
        return 0;
    }
    pq->head = 0;
    pq->tail = 0;
    pq->count = 0;
    pq->size = PACKET_QUEUE_SIZE;
    // memset(pq->pkt, 0, sizeof(packet_buffer_t) * size);
    return 1;
}
bool packet_queue_is_full(packet_queue_t *pq)
{
    return pq->count == pq->size;
}
bool packet_queue_is_empty(packet_queue_t *pq)
{
    return pq->count == 0;
}
int packet_queue_push(packet_queue_t *pq, packet_t *pkt)
{
    if (packet_queue_is_full(pq)) {
        return 0;
    }
    pq->pkt[pq->head] = pkt;
    pq->head++;
    if (pq->head >= pq->size)
    {
        pq->head = 0;
    }
    pq->count++;
    return 1;
}
int packet_queue_pop(packet_queue_t *pq, packet_t **pkt)
{
    if (packet_queue_is_empty(pq)) {
        return 0;
    }
    *pkt = pq->pkt[pq->tail];
    pq->tail++;
    if (pq->tail >= pq->size)
    {
        pq->tail = 0;
    }
    pq->count--;
    return 1;
}

uint16_t packet_queue_get_len(packet_queue_t *pq)
{
    return pq->count;
}
uint16_t packet_queue_get_space(packet_queue_t *pq)
{
    return pq->size - pq->count;
}