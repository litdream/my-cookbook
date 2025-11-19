package main

import (
	"fmt"
	"math"
)

type Shape interface {
	Area() float64
}

type Circle struct {
	Radius float64
}

type Square struct {
	Side float64
}

func (c *Circle) Area() float64 {
	return math.Pi * c.Radius * c.Radius
}

func (s *Square) Area() float64 {
	return s.Side * s.Side
}

func main() {
	fmt.Println("Go Interface-Based Polymorphism Demonstration\n")

	circle := &Circle{Radius: 7.0}
	square := &Square{Side: 5.0}

	fmt.Printf("Circle (Radius 7.0) Area: %.2f\n", circle.Area())
	fmt.Printf("Square (Side 5.0) Area: %.2f\n", square.Area())

	var shapes []Shape = []Shape{
		circle,
		square,
		&Circle{Radius: 3.0}, 
	}

	var totalArea float64 = 0.0
	for i, shape := range shapes {
		area := shape.Area()
		fmt.Printf("Shape %d: Area = %.2f\n", i+1, area)
		totalArea += area
	}
	fmt.Println("-----------------------------")
	fmt.Printf("Total Area of all shapes: %.2f\n", totalArea)
}
