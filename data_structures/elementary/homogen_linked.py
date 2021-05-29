free = 0
class free_list:
    def __init__(self, size):
        # The free list will contain the index to be allocated (the index itself) and the
        # location of the next index that is the be the free "head"
        self.free_links = [x+1 for x in range(size-1)]
        self.free_links.append(None)

    # Allocate to the master list and deallocate from the free list
    def allocate(self):
        global free
        # Giving the allocated index to x and setting the allocated spot to
        # None
        x = free

        # If there are no more spaces to be allocated on the free list 
        if(self.free_links[free] == None):
            raise ValueError("Out of memory in the free list")
            
        # Saving the previous free value to travel to and setting it zero after
        prev_free_val = self.free_links[free]
        self.free_links[free] = None

        # Moving the free "pointer" (really is just the index)
        free = prev_free_val

        return x

    # Deallocate for the master list and allocate back to the free list
    def deallocate(self, x):
        global free
        if(self.free_links[x] != None):
            raise ValueError("The value to be freed is already freed.")
        self.free_links[x] = free
        free = x

# Can only be created correctly if the size given is a multple of three
class homogen_list:
    # master_list contains the value of the items stored
    # next and prev contain the indexes of the respective next and
    # previous values (with respect to the index given)

    def __init__(self, size):
        if size % 3 != 0:
            raise ValueError("homogen_list must be initialized with a multiple of 3")

        # Making a free list for this master list and also the master list 
        self.free_memory = free_list(size)
        self.master_list = [None] * (3 * size)
        self.head = None
        self.size = size

    def length(self):
        return self.size

    # Use index function instead of directly indexing master_list
    def index(self, index):
        return index * 3

    def next_index(self, index):
        return self.index(index) + 1

    def prev_index(self, index):
        return self.index(index) + 2

    def allocate_object(self, element):
        x = self.free_memory.allocate()

        # Setting the spot allocated's value to the item placed in the list
        self.master_list[self.index(x)] = element

        # Setting the prev value of the newly allocated item to be the current head
        self.master_list[self.prev_index(x)] = self.head

        # Setting the current head's next to be the newly allocated item
        # If the self.head is not None (if it is not the very first
        # self.head which is set to None)
        if (self.head != None):
            self.master_list[self.next_index(self.head)] = x
        self.head = x

    def deallocate_object(self, index):
        # Allocating back to the free list
        self.free_memory.deallocate(index)


        # Empty the indexed link and set the previous' next to the next and the next's prev to the previous
        prev_head = self.prev_index(self.head)
        self.master_list[self.index(index)] = None
        self.master_list[self.prev_index(self.master_list[self.next_index(index)])] = self.master_list[self.prev_index(index)]
        self.master_list[self.next_index(self.master_list[self.prev_index(index)])] = self.master_list[self.next_index(index)]
        self.master_list[self.index(index)] = None
        self.master_list[self.prev_index(index)] = None
        self.master_list[self.next_index(index)] = None


def print_list(linked_List):
    x = 0
    print("Here are the values within the linked list: ")
    while(x != None):
        value = linked_List.master_list[linked_List.index(x)]
        print(value)
        x = linked_List.master_list[linked_List.next_index(x)]

def main():
    # The value of starter must be changed every time something is freed
    # added to the linked list
    linked_list = homogen_list(9);

    # Allocating one object to the linked list and printing out the free list and the master list between each allocation
    linked_list.allocate_object(5)
    print_list(linked_list)

    linked_list.allocate_object(6)
    print_list(linked_list)

    linked_list.allocate_object(7)
    print_list(linked_list)

    linked_list.allocate_object(8)
    print_list(linked_list)

    linked_list.allocate_object(9)
    print_list(linked_list)

    linked_list.allocate_object(10)
    print_list(linked_list)

    linked_list.allocate_object(11)
    print_list(linked_list)

    linked_list.allocate_object(12)
    print_list(linked_list)

    linked_list.deallocate_object(2)
    print("Just deallocated")
    print_list(linked_list)

    linked_list.allocate_object(7)
    print("Just allocated")
    print_list(linked_list)


main()
