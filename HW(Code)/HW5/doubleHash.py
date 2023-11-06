class DoubleHashTable:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size

    def primary_hash(self, key):
        return key % self.size

    def secondary_hash(self, key):
        return 7 - (key % 7)

    def double_hash(self, key, i):
        return (self.primary_hash(key) + i * self.secondary_hash(key)) % self.size

    def insert(self, key, value):
        index = self.primary_hash(key)
        if self.table[index] is None:
            self.table[index] = (key, value)
        else:
            i = 1
            new_index = self.double_hash(key, i)
            while self.table[new_index] is not None:
                i += 1
                new_index = self.double_hash(key, i)
                if new_index == index:  # This means we circled back to the start
                    raise Exception("Hash table is full or cannot find an empty slot")
            self.table[new_index] = (key, value)

    def __str__(self):
        return str(self.table)

# Example usage:
hash_table_size = 10  # Size of the hash table
double_hash_table = DoubleHashTable(hash_table_size)

# Insert integer key-value pairs
#4371, 1323, 6173, 4199, 4344, 9679, 1989
double_hash_table.insert(0, 4371)
double_hash_table.insert(1, 1323)
double_hash_table.insert(2, 6173)
double_hash_table.insert(3, 4199)  
double_hash_table.insert(4, 4344)
double_hash_table.insert(5, 9679)
double_hash_table.insert(6, 1989)

# Display the hash table
print(double_hash_table)
