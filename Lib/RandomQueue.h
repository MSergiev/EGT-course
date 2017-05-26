#ifndef RANDOMQUEUE_H_
#define RANDOMQUEUE_H_

class RandomQueue
{
public:
	RandomQueue();
	~RandomQueue();
public:
	void addElement( int );
	int removeElement();
private:
	void expandArr();
	// Identical to shuffleArr from Lib1.h but copied as a class member to avoid linker issues
	void shuffleArr( int*, int );
private:
	int* arr;
	int length;
	int size;
};

#endif /* RANDOMQUEUE_H_ */
