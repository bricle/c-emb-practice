#ifndef PACKET_QUEUE_H
#define PACKET_QUEUE_H

#include <stdint.h>
#include <stdbool.h>
/*
 * Ownership rule:
 *
 * packet_queue_push() success:
 *   ownership of pkt is transferred to the queue.
 *   Caller must not modify or free pkt until it is popped back.
 *
 * packet_queue_push() failure:
 *   ownership remains with the caller.
 *
 * packet_queue_pop() success:
 *   ownership of pkt is transferred from the queue to the caller.
 *   Caller is responsible for processing or releasing it.
 *
 * packet_queue_pop() failure:
 *   no ownership transfer happens.
 */
#define PACKET_QUEUE_SIZE 8
#define PACKET_DATA_SIZE 64
struct packet
{
    uint8_t data[PACKET_DATA_SIZE];
    uint16_t len;
    uint8_t type;
};
typedef struct packet packet_t;
typedef struct
{
    packet_t *pkt[PACKET_QUEUE_SIZE];
    uint16_t head;
    uint16_t tail;

    // 已经压入的有效pkt长度
    uint16_t count;

    // 总空间长度
    uint16_t size;
} packet_queue_t;

int packet_queue_init(packet_queue_t *pq);
bool packet_queue_is_full(packet_queue_t *pq);
bool packet_queue_is_empty(packet_queue_t *pq);
int packet_queue_push(packet_queue_t *pq, packet_t *pkt);
int packet_queue_pop(packet_queue_t *pq, packet_t **pkt);

uint16_t packet_queue_get_len(packet_queue_t *pq);
uint16_t packet_queue_get_space(packet_queue_t *pq);

#endif