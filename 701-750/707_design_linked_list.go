// Problem: https://leetcode.com/problems/design-linked-list/description/
// Solution: https://leetcode.com/problems/design-linked-list/solutions/7611862/go-idiomatic-optimal-on2-beats-100-by-ze-qc2b/

type MyLinkedList struct {
    head *node
    tail *node
    len int
}

type node struct {
    prev *node
    next *node
    val int
}

func Constructor() MyLinkedList {
    head := new(node)
    tail := new(node)
    head.next = tail
    tail.prev = head
    return MyLinkedList{head: head, tail: tail}
}

func (l *MyLinkedList) Get(idx int) int {
    n := l.nodeAt(idx)
    if n == nil {
        return -1
    }
    return n.val
}

func (l *MyLinkedList) AddAtHead(val int)  {
    l.insertAfter(l.head, l.newNode(val))
}

func (l *MyLinkedList) AddAtTail(val int)  {
    l.insertBefore(l.tail, l.newNode(val))
}

func (l *MyLinkedList) AddAtIndex(idx int, val int)  {
    if idx < 0 || idx > l.len {
        return
    }
    newNode := l.newNode(val)
    if idx == l.len {
        l.insertBefore(l.tail, newNode)
        return
    }
    n := l.nodeAtUnchecked(idx)
    l.insertBefore(n, newNode)    
}

func (l *MyLinkedList) DeleteAtIndex(idx int)  {
    n := l.nodeAt(idx)
    if n == nil {
        return
    }
    l.remove(n)
}

func (l *MyLinkedList) newNode(val int) *node {
    return &node{val: val}
}

func (l *MyLinkedList) nodeAt(idx int) *node {
    if idx < 0 || idx >= l.len {
        return nil
    }
    return l.nodeAtUnchecked(idx)
}

func (l *MyLinkedList) nodeAtUnchecked(idx int) *node {
    var n *node
    if 2*idx >= l.len {
        n = l.tail.prev
        for i := l.len-1; i > idx; i-- {
            n = n.prev
        }
    } else {
        n = l.head.next
        for i := 0; i < idx; i++ {
            n = n.next
        }
    }
    return n
}

func (l *MyLinkedList) insertAfter(at *node, n *node) {
    l.insertBefore(at.next, n)
}

func (l *MyLinkedList) insertBefore(at *node, n *node) {
    n.prev = at.prev
    n.next = at
    at.prev.next = n
    at.prev = n
    l.len++
}

func (l *MyLinkedList) remove(n *node) {
    n.prev.next = n.next
    n.next.prev = n.prev
    l.len--
}
