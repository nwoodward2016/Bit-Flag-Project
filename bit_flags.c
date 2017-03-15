/*****************************************************************************
	Author: Nathaniel Woodward
	Date: 2 / 9 / 16
	Effort: 3 Hours
	Purpose: To make an opaque bit-flag object type and
		program necesary functions to change the bit-flag object
	Interface Proposal: What is missing from this data structure is 
		additional functions. One function I could have added is a print
		function. This is necesary because in a main driver testing this
		function, there will be code intended to print out the bit flags
		in the object that is repeated over and over in the main source file.
		One could simply make this by looping through i=0 through
		bitFlag->size and using the check flag to print either a 1 or 0.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "bit_flags.h"

struct bit_flag
{
	int size;
	int capacity;
	int* data;
};
typedef struct bit_flag bitFlag;

BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits)
{
	int temp, i;
	bitFlag* pFlag = (bitFlag*)malloc(sizeof(bitFlag));
	temp = (number_of_bits / 32) + 1;

	pFlag->size = number_of_bits;
	pFlag->capacity = 32 * temp;
	pFlag->data = (int*)malloc(sizeof(int) * temp);
	
	for (i = 0; i < temp; i++) {
		pFlag->data[i] = 0;
	}

	return pFlag;
}

Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	int new, index, shift, i;
	int* temp;
	bitFlag* pFlag = hBit_flags;

	new = 1;
	index = flag_position / 32;
	shift = flag_position % 32;

	if (pFlag->size >= pFlag->capacity)
	{
		temp = (int*)malloc(sizeof(int) * pFlag->capacity * 2);
		if (temp == NULL)
		{
			return FAILURE;
		}
		for (i = 0; i < pFlag->size; i++)
		{
			temp[i] = pFlag ->data[i];
		}
		free(pFlag->data);
		pFlag->data = temp;
		pFlag->capacity *= 2;
	}

	new <<= shift;
	pFlag->data[index] = pFlag->data[index] | new;
	pFlag->size++;
	
	return SUCCESS;
}

Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	int temp, index, shift;
	bitFlag* pFlag = (bitFlag*)hBit_flags;

	if (pFlag == NULL) {
		return FAILURE;
	}
	
	temp = 1;
	index = flag_position / 32;
	shift = flag_position % 32;

	temp <<= shift;
	temp = ~temp;
	pFlag->data[index] = pFlag->data[index] & temp;
	
	return SUCCESS;
}

int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	int temp, result, index, shift, size;
	bitFlag* pFlag = (bitFlag*)hBit_flags;

	size = bit_flags_get_size(pFlag);
	if (flag_position > size) {
		return -1;
	}

	temp = 1;
	index = flag_position / 32;
	shift = flag_position % 32;

	temp <<= shift;
	result = pFlag->data[index] & temp;

	if (result == 0) {
		return 0;
	}
	else
		return 1;

}

int bit_flags_get_size(BIT_FLAGS hBit_flags)
{
	bitFlag* pFlag = (bitFlag*)hBit_flags;

	return pFlag->size;
}

int bit_flags_get_capacity(BIT_FLAGS hBit_flags)
{
	bitFlag* pFlag = (bitFlag*)hBit_flags;

	return pFlag->capacity;
}

void bit_flags_destroy(BIT_FLAGS* phBit_flags)
{
	bitFlag* pFlag = (bitFlag*)*phBit_flags;
	free(pFlag->data);
	free(pFlag);

	*phBit_flags = NULL;
}
