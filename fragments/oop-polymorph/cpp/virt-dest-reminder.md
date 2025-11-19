# C++ Virtual Destructor

It's been a while handling c++, and I forgot about virtual destructor in c++ inheritance.  (virtual relationship)

Reminder:


## Gemini

That is an extremely important question, and it shows you're thinking critically about C++ memory management\! The virtual destructor is arguably the most critical and often-forgotten part of using polymorphism with pointers.

The short answer is: **We need a virtual destructor to prevent memory leaks and undefined behavior when deleting a derived class object through a base class pointer.**

Let's break down why this happens, specifically referencing the cleanup section in your `main.cpp`:

```cpp
for (Shape* shape : shapes) {
    delete shape; // The problem lies here if ~Shape() wasn't virtual
}
```

### The Problem: Deleting through a Base Pointer

When you use C++ polymorphism, you store objects of different derived types (like `Circle` and `Square`) in a container of base class pointers (`Shape*`).

When the program executes `delete shape;`, the compiler needs to decide which destructor to call.

#### Scenario 1: **NO Virtual Destructor** (Dangerous\!)

1.  The compiler sees that `shape` is a `Shape*`.
2.  The destructor call is resolved **statically** (at compile time) based *only* on the pointer type.
3.  Only the **Base Class Destructor** (`~Shape()`) is called.
4.  **Result:** The destructor for the derived class (`~Circle()` or `~Square()`) is skipped. If those derived objects allocated any resources (like memory, file handles, or network connections), those resources are **never released**, leading to a **memory leak** and potentially undefined behavior.

#### Scenario 2: **WITH Virtual Destructor** (Correct\!)

1.  Because the base class destructor is marked `virtual` (`virtual ~Shape() {}`), the compiler knows to use the V-table (virtual table) for dispatch.
2.  When `delete shape;` is executed, the program looks at the **actual object type** pointed to (e.g., a `Circle`).
3.  The **Derived Class Destructor** (`~Circle()`) is called first, ensuring all derived resources are cleaned up.
4.  The **Base Class Destructor** (`~Shape()`) is then automatically called afterward.
5.  **Result:** The memory and resources are properly cleaned up in the correct order.

### The Rule of Thumb

If a class has **any** virtual functions (like your `area()` function), you **must** give it a `virtual` destructor. If you plan to inherit from a class and delete objects through a base class pointer, this rule is non-negotiable for stable C++ code.
