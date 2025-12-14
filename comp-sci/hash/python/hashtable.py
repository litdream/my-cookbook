import os

class HashTable:
    # Default capacity 10
    def __init__(self, capacity=10):
        self.capacity = capacity
        self.buckets = []
        for _ in range(capacity):
            self.buckets.append( [])

    def _hash(self, obj):
        return hash(obj) % self.capacity


    def put(self, key, value):
        index = self._hash(key)
        chain = self.buckets[index]

        # Checking if the pair(key, value) was used before:
        for i, (old_key, _) in enumerate(chain):
            if old_key == key:
                # Found the previous use.  Updating
                chain[i] = (key, value)  
                return

        # Key hasn't been used.  appending the pair
        chain.append( (key,value))

    def get(self, key):
        index = self._hash(key)
        chain = self.buckets[index]

        for existing_key, value in chain:
            if existing_key == key:
                return value
        raise KeyError(f"Key not found: {key}")

    def delete(self, key):
        index = self._hash(key)
        chain = self.buckets[index]

        # Checking if the pair(key, value) was used before:
        for i, (old_key, _) in enumerate(chain):
            if old_key == key:
                # Found the previous use.  Updating
                del chain[i]
                return
        raise KeyError(f"Key not found: {key}")


    ## Convenience Methods
    def __setitem__(self, key, value):
        self.put(key, value)
    def __getitem__(self, key):
        return self.get(key)

    def __str__(self):
        return self.buckets.__str__()
