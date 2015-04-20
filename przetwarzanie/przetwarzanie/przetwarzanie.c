#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
	char *text;
	struct lista *next;

}lista;

typedef struct
{
	int hash;
	struct lista *wsk;

	struct pierscien *next;
	struct pierscien *before;

}pierscien;

void show_everything(pierscien* pierwszy)
{

	lista *obecny = malloc(sizeof *obecny);
	pierwszy = pierwszy->next;

	while (pierwszy->wsk != NULL)
	{
		obecny = pierwszy->wsk;
		printf("Hash listy- %d \n", pierwszy->hash);
		while (obecny != NULL)
		{
			printf("%s\n", obecny->text);
			obecny = obecny->next;
		}
		pierwszy = pierwszy->next;
	}
	printf("\n");
}

pierscien usun(pierscien *root, int hash)
{
	root = root->next;
	while (root->wsk != NULL)
	{
		if (root->hash == hash)
			break;
		root = root->next;
	}
	pierscien *usuwany = malloc(sizeof *usuwany);
	usuwany = root;
	root = root->next;
	root->before = usuwany->before;
	root = root->before;
	root->next = usuwany->next;
	lista *obecny = malloc(sizeof *obecny);
	lista *nastepnik = malloc(sizeof *obecny);
	obecny = usuwany->wsk;
	while (obecny = NULL)
	{
		nastepnik = obecny->next;
		free(obecny->text);
		free(obecny);
		obecny = nastepnik;
	}

	free(usuwany);

	while (root->wsk != NULL)
		root = root->next;

	return *root;
}

void show(pierscien* pierwszy, int hash)
{
	pierscien *root = malloc(sizeof *root);
	root = pierwszy;
	pierwszy->next;
	while (pierwszy != NULL)
	{
		//printf("Ten hash to: %d \n", pierwszy->hash);
		if (pierwszy->hash == hash)
			break;
		if (pierwszy == root)
		{
			printf("Nie istnieje \n");
			return;
		}
		pierwszy = pierwszy->next;
		
	}

	lista *obecny = malloc(sizeof *obecny);

	obecny = pierwszy->wsk;
	while (obecny != NULL)
	{
		printf("%s\n", obecny->text);
		obecny = obecny->next;
	}
	printf("\n");
	//for (int i = 0; my_string[i] != NULL; i++)
	//	printf("%c", my_string[i]);
}

int hashuj(char *tab)
{
	int wynik = 0;
	//printf("%s", tab);
	for (int i = 0; tab[i] != NULL; i++)
		wynik += tab[i];
	
	wynik = wynik % 8;
	printf("%d\n", wynik);

	return wynik;
}


pierscien insert(pierscien *root, char *tab)
{
	int hash = hashuj(tab);
	int size = 0;
	lista *first = malloc(sizeof *first);
	first->next = NULL;
	bool czy_istnieje = false;
	//strcpy(first->text, tab);
	first->text = tab;
	//pierscien *poczatkowy = root;
	pierscien *nastepny = malloc(sizeof *nastepny);
	nastepny->hash = hash;
	nastepny->wsk = first;

	if (root->next == root)
	{
		nastepny->next = root;
		nastepny->before = root;
		//tekst tez ustalony
		//hash juz ustalony

		root->next = nastepny;
		root->before = nastepny;
		return *root;
	}

	root = root->next;
	while (root->hash != NULL) //czy root->next != NULL
	{
		//printf("To jest: %d \n", root->hash);
		if (root->hash == hash)
		{
			czy_istnieje = true;
			break;
		}
		root = root->next;
		size++;
	}

	///*if (root->hash == hash)
	//*/	czy_istnieje = true;

	
	
	if (czy_istnieje)// czy wchodze
	{
		//printf("Jestem tu");
		lista *obecny = malloc(sizeof *obecny);
		obecny = root->wsk;

		while (obecny->next != NULL)
		{
			if (strcmp(obecny->text, first->text) < 0)
				obecny = obecny->next;
			else
				break;
		}
		first->next = obecny->next;
		obecny->next = first;

		//nastepny->wsk = 
	}
	else
	{
		if (size == 1) //tylko dwa elementy
		{
			//root = root->next;
			if (nastepny->hash > root->hash)
			{
				nastepny->next = root;
				root->before = nastepny;

				root = root->next;

				nastepny->before = root;
				root->next = nastepny;

				root = root->before;
				return *root;
			}
			else
			{
				root->next = nastepny;
				nastepny->before = root;

				root = root->before;

				nastepny->next = root;
				root->before = nastepny;

				root = root->next;
				return *root;
			}
		}
		root = root->next;
		while (root->hash != NULL)
		{
			if (nastepny->hash <= root->hash)
			{
				nastepny->next = root;
				root = root->before;
				root->next = nastepny;
				nastepny->before = root;
				root = nastepny->next;
				root->before = nastepny;
				break;
			}
			root = root->next;
		}
		if (root->hash == NULL)
		{
			nastepny->next = root;
			root = root->before;
			root->next = nastepny;
			nastepny->before = root;
			root = nastepny->next;
			root->before = nastepny;
		}
	}
	while (root->hash != NULL)
		root = root->next;
	return *root;
}


int main()
{
	
	//char rozkaz[30];
	char *rozkaz = malloc(sizeof *rozkaz);
	int index;
	printf("Wprowadz tekst:\n");


	//printf("%s", my_string);
	//lista *poczatek = malloc(sizeof *poczatek);
	//strcpy(poczatek->text, "karol");
	//poczatek->next = NULL;


	pierscien *root = malloc(sizeof *root);
	root->next = root;
	root->hash = NULL;
	root->before = root;
	root->wsk = NULL;

	while (true)
	{
		scanf("%30s", rozkaz);
		if (strcmp(rozkaz, "dodaj") == 0)
		{
			//char my_string[256];
			char *my_string = malloc(sizeof *my_string);
			scanf("%256s", my_string);
			*root = insert(root, my_string);
		}
		else if (strcmp(rozkaz, "pokaz") == 0)
		{
			//printf("Podaj wartosc hash: \n");
			
			scanf("%d", &index);
			show(root, index);
		}
		else if (strcmp(rozkaz, "wszystko") == 0)
		{
			show_everything(root);
		}
		else if (strcmp(rozkaz, "usun") == 0)
		{
			scanf("%d", &index);
			*root = usun(root, index);
		}
		
	}



	system("PAUSE");
	return 0;
}