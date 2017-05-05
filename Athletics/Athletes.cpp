#include "Athletes.h"

Athletes::Athletes(string firstName, string lastName, float best, string nationality) {
	this->firstName = firstName;
	this->lastName = lastName;
	this->best = best;
	this->nationality = nationality;
}

Athletes::~Athletes() {

}

void Athletes::setFirstName(const string firstName) {
	this->firstName = firstName;
}

void Athletes::setLastName(const string lastName) {
	this->lastName = lastName;
}

void Athletes::setBest(const float best) {
	this->best = best;
}

void Athletes::setNationality(const string nationality) {
	this->nationality = nationality;
}

const string Athletes::getFirstName() const {
	return firstName;
}

const string Athletes::getLastName() const {
	return lastName;
}

const float Athletes::getBest() const {
	return best;
}

const string Athletes::getNationality() const {
	return nationality;
}
