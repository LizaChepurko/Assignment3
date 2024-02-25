
#include "StrList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100

int main() {
	StrList *list = StrList_alloc();

	if (list == NULL)
	{
		printf("Error: StrList_alloc returned NULL\n");
		return 1;
	}

	int n = -1;
	int t = 1;

	while (t)
	{
		scanf("%d", &n);

		switch (n)
		{
			case 0:
			{
				t = 0;
				printf("\n");
				break;
			}

			case 1:
			{
				int numOfWords;
				scanf("%d", &numOfWords);
				
				for (int i = 0; i < numOfWords; ++i)
				{
					char data[MAX_WORD_LENGTH] = {0};
					scanf("%s", data);
					StrList_insertLast(list, data);
				}

				break;
			}

			case 2:
			{
				int insertInIndex;
				scanf("%d", &insertInIndex);
				char newdata[MAX_WORD_LENGTH] = {0};
				scanf("%s", newdata);
				StrList_insertAt(list, newdata, insertInIndex);
				insertInIndex++;
				break;
			}
			case 3:
			{
				StrList_print(list);
				break;
			}

			case 4:
			{
				printf("%ld\n", StrList_size(list));
				break;
			}

			case 5:
			{
				int index;
				scanf("%d", &index);
				StrList_printAt(list, index);
				break;
			}
			case 6:
			{
				printf("%d\n", StrList_printLen(list));
				break;
			}
			case 7:
			{
				char s[MAX_WORD_LENGTH] = {0};
				scanf("%s", s);
				printf("%d\n", StrList_count(list, s));
				break;
			}

			case 8:
			{
				char s[MAX_WORD_LENGTH] = {0};
				scanf("%s", s);
				StrList_remove(list, s);
				break;
			}

			case 9:
			{
				int index;
				scanf("%d", &index);
				StrList_removeAt(list, index);
				break;
			}

			case 10:
			{
				StrList_reverse(list);
				break;
			}

			case 11:
			{
				StrList_free(list);
				// Reallocate the list to avoid dangling pointer
				list = StrList_alloc();
				break;
			}

			case 12:
			{
				StrList_sort(list);
				break;
			}

			case 13:
			{
				printf("%s\n", (StrList_isSorted(list) ? "true":"false"));
				break;
			}
		}
	}

	StrList_free(list);
	return 0;
}