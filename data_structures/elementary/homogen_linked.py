def main():
    # The value of starter must be changed every time something is freed
    # added to the linked list
    starter = 0;
    linked_list = homogen_list(9);
    
class free_list:
    def __init__(self, size, master_list):
        
        # First value is 0
        self.free.append(0)

        # Next index is 3
        self.free.append(3)

        # Prev index is None
        self.free.append(None)

        # Appending the middle items
        for i+1 in range(size-2):
            self.free.append(i)
            self.free.append((3 + (3 * i)))
            self.free.append((3 * (i - 1)))
        
        # Appending the last item
        self.free.append(size - 1)
        self.free.append(None)
        self.free.append(size - 6)

    # Allocate to the master list and deallocate from the free list
    def allocate(self):
        x = free

        try:
            if(free + 1 > len(self.list)):
                raise ValueError
        
        except ValueError:
            print("Out of memory in the free list")

        free = free + 1

        return x

    # Deallocate for the master list and allocate from the free list
    def deallocate(self):
        try:
            if(free = 0):
                raise ValueError
        except ValueError:
            print("There is nothing to deallocate in the free list")

        x = free
        free = free - 1
        self.list[free] = x

# Can only be created correctly if the size given is a multple of three
class homogen_list:

    def __init__(self, size):
        try:
            if size % 3 != 0:
                raise ValueError
        except ValueError:
            print("homogen_list must be initialized with a multiple of 3")

        self.master_list = [null] * (3 * size

    def index(self, index):
        return self.master_list[index * 3]

    def next(self, index):
        return self.master_list[self.index(index) + 1]

    def prev(self, index):
        return self.master_list[self.index(index) + 2]

# x is the object we want to store in the linked list
def allocate_object(x):
