lib1.h

	(+)1. lib function that formats a currency appropriately (and returns a string)
	(+)2. lib function that prints an array (initially specific types, later generic/template) or matrix,
	including columns, spacing tweaking
	(+)3. lib function to round a double to a specific number of digits (including after / before
	comma), that produces double (not string)
	4. lib function that produces quotient and reminder (returning struct)
	5. lib functions to help with random stuff: picking a number from a range, picking a double,
	selecting one or many items from an array, shuffling array, random queue (put
	elements, remove random); later -- abstract out the random generator from the
	functions (2 layer arch)
	6. lib to evaluate a hand of cards(returning ENUM) – see poker rules , blackjack rules, other
	card games rules
lib2.h
//...