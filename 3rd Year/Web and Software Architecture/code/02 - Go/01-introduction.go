package main

import "fmt"

var globalVar int = 10

func main() {
	fmt.Println("Hello World!")

	
	// Create the variable without assigning a value
	var anInteger int

	// Assignment of the value
	anInteger = 6

	// Inference: the type will be "float"
	var pi = 3.14

	// If we are not sure of how many bits we need, we can just use int or uint
	var anotherInteger uint = 14

	// Cast the second integer to an integer of type int64
	var mySum int64 = 5 + int64(anotherInteger)

	// Use the := notation instead of "var"
	eulernumber := 2.7183

	// We can also declare constants with the "const" keyword
	const g float32 = 9.81
}