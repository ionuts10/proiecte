#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 99999

typedef struct Graf_Metrou
{
	int nr_statii, nr_tuneluri;
	int **matrice_de_adiacenta_distanta;
}Graf_Metrou;

typedef struct Client
{
	char *nume_client;
	int timp_fata_de_statie_de_metrou;
	int suma_de_platit;
}Client;

typedef struct Statie_Metrou
{
	char *nume_statie;
	int comenzi_livrate_client;
	int numar_clienti;
	Client *cl;
}Statie_Metrou;

typedef struct Graf_Clienti
{
	int nr_clienti, nr_strazi;
	int **matrice_de_adiacenta_timp;
}Graf_Clienti;

void citire_date(FILE *fisier, Graf_Metrou **g_m, Graf_Clienti ***g_c, Statie_Metrou **statie)
{
	int i, j, k;

	*g_m = malloc(sizeof(Graf_Metrou));

	// Citire numar statii si initializarea matricei de adiacenta pentru distanta
	fscanf(fisier, "%d\n", &(*g_m)->nr_statii);

	(*g_m)->matrice_de_adiacenta_distanta = malloc(sizeof(int*) * (*g_m)->nr_statii);
	for(i = 0; i < (*g_m)->nr_statii; i++)
	{
		(*g_m)->matrice_de_adiacenta_distanta[i] = calloc((*g_m)->nr_statii, sizeof(int));
	}

	*statie = malloc(sizeof(Statie_Metrou) * (*g_m)->nr_statii);

	*g_c = malloc(sizeof(Graf_Clienti*) * (*g_m)->nr_statii);
	
	for(i = 0; i < (*g_m)->nr_statii; i++)
	{
		(*g_c)[i] = malloc(sizeof(Graf_Clienti));
	}

	// Citirea datelor clientilor din fiecare statie
	for(i = 0; i < (*g_m)->nr_statii; i++)
	{
		char buffer1[25];

		fscanf(fisier, "%s\n%d\n", buffer1, &(*statie)[i].numar_clienti);
		(*statie)[i].nume_statie = malloc(sizeof(char) * (strlen(buffer1) +1 ));
		strcpy((*statie)[i].nume_statie, buffer1);
		(*statie)[i].comenzi_livrate_client = 0;

		(*g_c)[i]->nr_clienti = (*statie)[i].numar_clienti;
		(*g_c)[i]->matrice_de_adiacenta_timp = malloc(sizeof(int*) * ((*g_c)[i]->nr_clienti + 1));
		for(j = 0; j <= (*g_c)[i]->nr_clienti; j++)
		{
			(*g_c)[i]->matrice_de_adiacenta_timp[j] = calloc(((*g_c)[i]->nr_clienti + 1), sizeof(int));
		}

		// Citirea vectorului ce contine detaliile clientilor unei statii "i"
		(*statie)[i].cl = malloc(sizeof(Client) * ((*statie)[i].numar_clienti + 1));

		(*statie)[i].cl[0].timp_fata_de_statie_de_metrou = 0;
		(*statie)[i].cl[0].suma_de_platit = 0;
		(*statie)[i].cl[0].nume_client = malloc(sizeof(char) * 3);
		strcpy((*statie)[i].cl[0].nume_client, "sS");

		for(j = 1; j <= (*statie)[i].numar_clienti; j++)
		{
			char buffer2[25];

			fscanf(fisier, "\t%s\n\t%d\n\t%d\n", buffer2, &(*statie)[i].cl[j].timp_fata_de_statie_de_metrou, &(*statie)[i].cl[j].suma_de_platit);
			(*statie)[i].cl[j].nume_client = malloc(sizeof(char) * (strlen(buffer2) + 1));
			strcpy((*statie)[i].cl[j].nume_client, buffer2);
			(*g_c)[i]->matrice_de_adiacenta_timp[0][j] = (*g_c)[i]->matrice_de_adiacenta_timp[j][0] = (*statie)[i].cl[j].timp_fata_de_statie_de_metrou;
		}

		// Crearea matricei de adiacenta pentru clientii statiei "i"
		fscanf(fisier, "%d\n", &(*g_c)[i]->nr_strazi);
		for(j = 0; j < (*g_c)[i]->nr_strazi; j++)
		{
			char client1[25], client2[25];
			int poz1, poz2, dist;
			int ok = 0;

			fscanf(fisier, "%s %s %d\n", client1, client2, &dist);
			for(k = 1; k <= (*g_c)[i]->nr_clienti; k++)
			{
				if(!strcmp((*statie)[i].cl[k].nume_client, client1))
				{
					poz1 = k;
					ok++;
				}
				else if(!strcmp((*statie)[i].cl[k].nume_client, client2))
				{
					poz2 = k;
					ok++;
				}
				if(ok == 2)
				{
					break;
				}
			}
			(*g_c)[i]->matrice_de_adiacenta_timp[poz1][poz2] = (*g_c)[i]->matrice_de_adiacenta_timp[poz2][poz1] = dist;
		}

		//Afisare matrice de adiacenta clienti
		/*for(j = 0; j <= (*g_c)[i]->nr_clienti; j++)
		{
			for(k = 0; k <= (*g_c)[i]->nr_clienti; k++)
			{
				printf("%d ", (*g_c)[i]->matrice_de_adiacenta_timp[j][k]);
			}
			printf("\n");
		}*/
	}

	// Crearea matricei de adiacenta statii metrou
	fscanf(fisier, "%d\n", &(*g_m)->nr_tuneluri);
	for(i = 0; i < (*g_m)->nr_tuneluri; i++)
	{
		char statie1[25], statie2[25];
		int poz1, poz2, dist;
		int ok = 0;

		fscanf(fisier, "%s %s %d\n", statie1, statie2, &dist);
		for(j = 0; j < (*g_m)->nr_statii; j++)
		{
			if(!strcmp((*statie)[j].nume_statie, statie1))
			{
				poz1 = j;
				ok++;
			}
			else if(!strcmp((*statie)[j].nume_statie, statie2))
			{
				poz2 = j;
				ok++;
			}
			if(ok == 2)
			{
				break;
			}
		}
		(*g_m)->matrice_de_adiacenta_distanta[poz1][poz2] = (*g_m)->matrice_de_adiacenta_distanta[poz2][poz1] = dist;
	}

	// Afisare matrice de adiacenta statii metrou
	/*for(j = 0; j < (*g_m)->nr_statii; j++)
	{
		for(k = 0; k < (*g_m)->nr_statii; k++)
		{
			printf("%d ", (*g_m)->matrice_de_adiacenta_distanta[j][k]);
		}
		printf("\n");
	}*/
}

void conexiune(FILE *fisier_date, FILE *fisier_rezultate, Graf_Metrou *g_m, Graf_Clienti **g_c, Statie_Metrou *statie)
{
	char client1[25], client2[25];
	int i, j, poz1 = 0, poz2 = 1, ok = 0;

	fscanf(fisier_date, "%s %s\n", client1, client2);
	
	for(i = 0; i < g_m->nr_statii; i++)
	{
		for(j = 1; j <= statie[i].numar_clienti; j++)
		{
			if(!strcmp(statie[i].cl[j].nume_client, client1))
			{
				ok++;
				poz1 = j;
			}
			else if(!strcmp(statie[i].cl[j].nume_client, client2))
			{
				ok++;
				poz2 = j;
			}
			if(ok == 2)
			{
				break;
			}
		}
		if(ok == 2)
		{
			if(g_c[i]->matrice_de_adiacenta_timp[poz1][poz2] != 0)
			{
				fprintf(fisier_rezultate, "OK\n");
			}
			else
			{
				fprintf(fisier_rezultate, "NO\n");
			}
			break;
		}
	}
}

void legatura(FILE *fisier_date, FILE *fisier_rezultate, Graf_Metrou *g_m, Statie_Metrou *statie)
{
	char statie1[25];
	int i, poz = -1;
	
	fscanf(fisier_date, "%s\n", statie1);
	for(i = 0; i < g_m->nr_statii; i++)
	{
		if(!strcmp(statie[i].nume_statie, statie1))
		{
			poz = i;
			break;
		}
	}
	if(poz != -1)
	{
		for(i = 0; i < g_m->nr_statii; i++)
		{
			if(g_m->matrice_de_adiacenta_distanta[i][poz] != 0 && g_m->matrice_de_adiacenta_distanta[i][poz] != INF)
			{
				fprintf(fisier_rezultate, "%s ", statie[i].nume_statie);
			}
		}
	}
	fprintf(fisier_rezultate, "\n");
}

void blocaj_tunel(FILE *fisier_date, FILE *fisier_rezultate, Graf_Metrou *g_m, Statie_Metrou *statie)
{
	char statie1[25], statie2[25];
	int i, poz1 = -1, poz2 = -1, dist, ok = 0;
	
	fscanf(fisier_date, "%s %s %d\n", statie1, statie2, &dist);
	for(i = 0; i < g_m->nr_statii; i++)
	{
		if(!strcmp(statie[i].nume_statie, statie1))
		{
			poz1 = i;
			ok++;
		}
		else if(!strcmp(statie[i].nume_statie, statie2))
		{
			poz2 = i;
			ok++;
		}
		if(ok == 2)
		{
			g_m->matrice_de_adiacenta_distanta[poz1][poz2] = g_m->matrice_de_adiacenta_distanta[poz2][poz1] = INF;
			break;
		}
	}
}

void blocaj_strada(FILE *fisier_date, FILE *fisier_rezultate, Graf_Metrou *g_m, Graf_Clienti **g_c, Statie_Metrou *statie)
{
	char client1[25], client2[25];
	int i, j, poz1 = 0, poz2 = 1, ok = 0;

	fscanf(fisier_date, "%s %s\n", client1, client2);
	
	for(i = 0; i < g_m->nr_statii; i++)
	{
		for(j = 1; j <= statie[i].numar_clienti; j++)
		{
			if(!strcmp(statie[i].cl[j].nume_client, client1))
			{
				ok++;
				poz1 = j;
			}
			else if(!strcmp(statie[i].cl[j].nume_client, client2))
			{
				ok++;
				poz2 = j;
			}
			if(ok == 2)
			{
				break;
			}
		}
		if(ok == 2)
		{
			g_c[i]->matrice_de_adiacenta_timp[poz1][poz2] = g_c[i]->matrice_de_adiacenta_timp[poz2][poz1] = INF;
			break;
		}
	}
}

void adauga_ruta(FILE *fisier_date, FILE *fisier_rezultate, Graf_Metrou *g_m, Statie_Metrou *statie)
{
	char statie1[25], statie2[25];
	int i, poz1 = -1, poz2 = -1, dist, ok = 0;
	
	fscanf(fisier_date, "%s %s %d\n", statie1, statie2, &dist);
	for(i = 0; i < g_m->nr_statii; i++)
	{
		if(!strcmp(statie[i].nume_statie, statie1))
		{
			poz1 = i;
			ok++;
		}
		else if(!strcmp(statie[i].nume_statie, statie2))
		{
			poz2 = i;
			ok++;
		}
		if(ok == 2)
		{
			g_m->matrice_de_adiacenta_distanta[poz1][poz2] = g_m->matrice_de_adiacenta_distanta[poz2][poz1] = dist;
			break;
		}
	}
}

void sterge_ruta(FILE *fisier_date, FILE *fisier_rezultate, Graf_Metrou *g_m, Statie_Metrou *statie)
{
	char statie1[25], statie2[25];
	int i, poz1 = -1, poz2 = -1, dist, ok = 0;
	
	fscanf(fisier_date, "%s %s %d\n", statie1, statie2, &dist);
	for(i = 0; i < g_m->nr_statii; i++)
	{
		if(!strcmp(statie[i].nume_statie, statie1))
		{
			poz1 = i;
			ok++;
		}
		else if(!strcmp(statie[i].nume_statie, statie2))
		{
			poz2 = i;
			ok++;
		}
		if(ok == 2)
		{
			g_m->nr_tuneluri--;
			g_m->matrice_de_adiacenta_distanta[poz1][poz2] = g_m->matrice_de_adiacenta_distanta[poz2][poz1] = 0;
			break;
		}
	}
}

void adauga_strada(FILE *fisier_date, FILE *fisier_rezultate, Graf_Metrou *g_m, Graf_Clienti **g_c, Statie_Metrou *statie)
{
	char client1[25], client2[25];
	int i, j, poz1 = 0, poz2 = 1, ok = 0, dist;

	fscanf(fisier_date, "%s %s %d\n", client1, client2, &dist);
	
	for(i = 0; i < g_m->nr_statii; i++)
	{
		for(j = 1; j <= statie[i].numar_clienti; j++)
		{
			if(!strcmp(statie[i].cl[j].nume_client, client1))
			{
				ok++;
				poz1 = j;
			}
			else if(!strcmp(statie[i].cl[j].nume_client, client2))
			{
				ok++;
				poz2 = j;
			}
			if(ok == 2)
			{
				break;
			}
		}
		if(ok == 2)
		{
			g_c[i]->matrice_de_adiacenta_timp[poz1][poz2] = g_c[i]->matrice_de_adiacenta_timp[poz2][poz1] = dist;
			break;
		}
	}
}

void sterge_strada(FILE *fisier_date, FILE *fisier_rezultate, Graf_Metrou *g_m, Graf_Clienti **g_c, Statie_Metrou *statie)
{
	char client1[25], client2[25];
	int i, j, poz1 = 0, poz2 = 1, ok = 0;

	fscanf(fisier_date, "%s %s\n", client1, client2);
	
	for(i = 0; i < g_m->nr_statii; i++)
	{
		for(j = 1; j <= statie[i].numar_clienti; j++)
		{
			if(!strcmp(statie[i].cl[j].nume_client, client1))
			{
				ok++;
				poz1 = j;
			}
			else if(!strcmp(statie[i].cl[j].nume_client, client2))
			{
				ok++;
				poz2 = j;
			}
			if(ok == 2)
			{
				break;
			}
		}
		if(ok == 2)
		{
			g_c[i]->matrice_de_adiacenta_timp[poz1][poz2] = g_c[i]->matrice_de_adiacenta_timp[poz2][poz1] = 0;
			break;
		}
	}
}

int comenzi_neterminate(int *vizitat, int nr_clienti)
{
	int i;
	for(i = 0; i <= nr_clienti; i++)
	{
		if(vizitat[i] == 0)
		{
			return 0;
		}
	}
	return 1;
}

int timp_minim(int dist[], int sps[], int V)
{
	int i, min = INF, min_index;
	for(i = 1; i <= V; i++)
	{
		if(sps[i] == 0 && dist[i] <= min)
		{
			min = dist[i];
			min_index = i;
		}
	}
	return min_index;
}

int distanta_minima(int dist[], int sps[], int V)
{
	int i, min = INF, min_index;
	for(i = 0; i < V; i++)
	{
		if(sps[i] == 0 && dist[i] <= min)
		{
			min = dist[i];
			min_index = i;
		}
	}
	return min_index;
}

void drum_strada(FILE *fisier_date, FILE *fisier_rezultate, Graf_Metrou *g_m, Graf_Clienti **g_c, Statie_Metrou *statie)
{
	int i, j, u, poz1, poz2, ok = 0, statie_curenta;
	char client1[25], client2[25];

	fscanf(fisier_date, "%s %s\n", client1, client2);

	for(i = 0; i < g_m->nr_statii; i++)
	{
		for(j = 1; j <= statie[i].numar_clienti; j++)
		{
			if(!strcmp(statie[i].cl[j].nume_client, client1))
			{
				ok++;
				poz1 = j;
			}
			else if(!strcmp(statie[i].cl[j].nume_client, client2))
			{
				ok++;
				poz2 = j;
			}
			if(ok == 2)
			{
				break;
			}
		}
		if(ok == 2)
		{
			break;
		}
	}

	statie_curenta = i;
	int dist[statie[i].numar_clienti + 1];
	int sps[statie[i].numar_clienti + 1];
	int pred[statie[i].numar_clienti + 1];
	char adresa[statie[i].numar_clienti + 1][25];

	for(i = 1; i <= statie[statie_curenta].numar_clienti; i++)
	{
		dist[i] = INF;
		sps[i] = 0;
		pred[i] = -1;
	}

	dist[poz1] = 0;

	for(i = 1; i <= statie[statie_curenta].numar_clienti; i++)
	{
		u = timp_minim(dist, sps, g_c[statie_curenta]->nr_clienti);
		sps[u] = 1;
		for(j = 1; j <= statie[statie_curenta].numar_clienti; j++)
		{
			if(sps[j] == 0 && g_c[statie_curenta]->matrice_de_adiacenta_timp[u][j] != 0 && dist[u] != INF && dist[u] + g_c[statie_curenta]->matrice_de_adiacenta_timp[u][j] < dist[j])
			{
				dist[j] = dist[u] + g_c[statie_curenta]->matrice_de_adiacenta_timp[u][j];
				pred[j] = u;
			}
		}
	}

	strcpy(adresa[0], statie[statie_curenta].cl[poz2].nume_client);
	j = 1;
	while(poz2 != poz1)
	{
		for(i = 1; i <= statie[statie_curenta].numar_clienti; i++)
		{
			if(i == poz2)
			{
				strcpy(adresa[j++], statie[statie_curenta].cl[pred[i]].nume_client);
				poz2 = pred[i];
				break;
			}
		}
	}
	for(i = j-1; i >= 0; i--)
	{
		fprintf(fisier_rezultate, "%s ", adresa[i]);
	}
	fprintf(fisier_rezultate, "\n");
}

void drum_metrou(FILE *fisier_date, FILE *fisier_rezultate, Graf_Metrou *g_m, Statie_Metrou *statie)
{
	int i, j, u, poz1, poz2, ok = 0;
	int dist[g_m->nr_statii];
	int sps[g_m->nr_statii];
	int pred[g_m->nr_statii];
	char statie1[25], statie2[25];
	char adresa[g_m->nr_statii][25];

	fscanf(fisier_date, "%s %s\n", statie1, statie2);

	for(i = 0; i < g_m->nr_statii; i++)
	{
		if(!strcmp(statie[i].nume_statie, statie1))
		{
			poz1 = i;
			ok++;
		}
		else if(!strcmp(statie[i].nume_statie, statie2))
		{
			poz2 = i;
			ok++;
		}
		if(ok == 2)
		{
			break;
		}
	}

	for(i = 0; i < g_m->nr_statii; i++)
	{
		dist[i] = INF;
		sps[i] = 0;
		pred[i] = -1;
	}

	dist[poz1] = 0;

	for(i = 0; i < g_m->nr_statii; i++)
	{
		u = distanta_minima(dist, sps, g_m->nr_statii);
		sps[u] = 1;
		for(j = 0; j < g_m->nr_statii; j++)
		{
			if(sps[j] == 0 && g_m->matrice_de_adiacenta_distanta[u][j] != 0 && dist[u] != INF && dist[u] + g_m->matrice_de_adiacenta_distanta[u][j] < dist[j])
			{
				dist[j] = dist[u] + g_m->matrice_de_adiacenta_distanta[u][j];
				pred[j] = u;
			}
		}
	}

	strcpy(adresa[0], statie[poz2].nume_statie);
	j = 1;
	while(poz2 != poz1)
	{
		for(i = 0; i < g_m->nr_statii; i++)
		{
			if(i == poz2)
			{
				strcpy(adresa[j++], statie[pred[i]].nume_statie);
				poz2 = pred[i];
				break;
			}
		}
	}
	for(i = j-1; i >= 0; i--)
	{
		fprintf(fisier_rezultate, "%s ", adresa[i]);
	}
	fprintf(fisier_rezultate, "\n");
}

void timp_statie(FILE *fisier_date, FILE *fisier_rezultate, Graf_Metrou *g_m, Graf_Clienti **g_c, Statie_Metrou *statie)
{
	char statie1[25];
	int i, j, min, poz_min, poz = 0, timp = 0, val;
	int *vizitat;

	fscanf(fisier_date, "%s\n", statie1);

	for(i = 0; i < g_m->nr_statii; i++)
	{
		if(!strcmp(statie[i].nume_statie, statie1))
		{
			break;
		}
	}
	vizitat = calloc((g_c[i]->nr_clienti + 1), sizeof(int));
	vizitat[0] = 1;
	while(comenzi_neterminate(vizitat, g_c[i]->nr_clienti) == 0)
	{
		min = INF;
		for(j = 0; j <= g_c[i]->nr_clienti; j++)
		{
			val = g_c[i]->matrice_de_adiacenta_timp[poz][j];
			if(min > val && vizitat[j] == 0 && val != 0 && val != INF)
			{
				min = g_c[i]->matrice_de_adiacenta_timp[poz][j];
				poz_min = j;
			}
		}
		timp += min;
		poz = poz_min;
		vizitat[poz] = 1;
	}
	timp += g_c[i]->matrice_de_adiacenta_timp[0][poz];
	free(vizitat);
	fprintf(fisier_rezultate, "%d\n", timp);
}

void comanda_statie(FILE *fisier_date, FILE *fisier_rezultate, Graf_Metrou *g_m, Graf_Clienti **g_c, Statie_Metrou *statie)
{
	int valoare_suma, suma_statie, i, j;

	fscanf(fisier_date, "%d\n", &valoare_suma);

	for(i = 0; i < g_m->nr_statii; i++)
	{
		suma_statie = 0;

		for(j = 1; j <= statie[i].numar_clienti; j++)
		{
			suma_statie += statie[i].cl[j].suma_de_platit;
		}

		if(suma_statie >= valoare_suma)
		{
			fprintf(fisier_rezultate, "%s ", statie[i].nume_statie);
		}
	}
	fprintf(fisier_rezultate, "\n");
}


void rezolvare_cerinte(FILE *fisier_date, FILE *fisier_rezultate, Graf_Metrou *g_m, Graf_Clienti **g_c, Statie_Metrou *statie)
{
	int nr_cerinte, i;
	char cerinta[20];

	fscanf(fisier_date, "%d\n", &nr_cerinte);

	for(i = 0; i < nr_cerinte; i++)
	{
		fscanf(fisier_date, "%s ", cerinta);
		if(!strcmp(cerinta, "conexiune"))
		{
			conexiune(fisier_date, fisier_rezultate, g_m, g_c, statie);
		}
		else if(!strcmp(cerinta, "legatura"))
		{
			legatura(fisier_date, fisier_rezultate, g_m, statie);
		}
		else if(!strcmp(cerinta, "blocaj_tunel"))
		{
			blocaj_tunel(fisier_date, fisier_rezultate, g_m, statie);
		}
		else if(!strcmp(cerinta, "blocaj_strada"))
		{
			blocaj_strada(fisier_date, fisier_rezultate, g_m, g_c, statie);
		}
		else if(!strcmp(cerinta, "adauga_ruta"))
		{
			adauga_ruta(fisier_date, fisier_rezultate, g_m, statie);
		}
		else if(!strcmp(cerinta, "sterge_ruta"))
		{
			sterge_ruta(fisier_date, fisier_rezultate, g_m, statie);
		}
		else if(!strcmp(cerinta, "adauga_strada"))
		{
			adauga_strada(fisier_date, fisier_rezultate, g_m, g_c, statie);
		}
		else if(!strcmp(cerinta, "sterge_strada"))
		{
			sterge_strada(fisier_date, fisier_rezultate, g_m, g_c, statie);;
		}
		else if(!strcmp(cerinta, "drum_strada"))
		{
			drum_strada(fisier_date, fisier_rezultate, g_m, g_c, statie);
		}
		else if(!strcmp(cerinta, "drum_metrou"))
		{
			drum_metrou(fisier_date, fisier_rezultate, g_m, statie);
		}
		else if(!strcmp(cerinta, "timp_statie"))
		{
			timp_statie(fisier_date, fisier_rezultate, g_m, g_c, statie);
		}
		else if(!strcmp(cerinta, "comanda_statie"))
		{
			comanda_statie(fisier_date, fisier_rezultate, g_m, g_c, statie);
		}
	}
}

void eliberare_memorie(Graf_Metrou **g_m, Graf_Clienti ***g_c, Statie_Metrou **statie)
{
	int i, j;
	for(i = 0; i < (*g_m)->nr_statii; i++)
	{
		free((*statie)[i].nume_statie);

		for(j = 0; j <= (*g_c)[i]->nr_clienti; j++)
		{
			free((*g_c)[i]->matrice_de_adiacenta_timp[j]);
		}
		free((*g_c)[i]->matrice_de_adiacenta_timp);
		for(j = 0; j <= (*statie)[i].numar_clienti; j++)
		{
			free((*statie)[i].cl[j].nume_client);
		}
		free((*statie)[i].cl);

	}
	free((*statie));
	for(i = 0; i < (*g_m)->nr_statii; i++)
	{
		free((*g_m)->matrice_de_adiacenta_distanta[i]);
	}
	free((*g_m)->matrice_de_adiacenta_distanta);
	for(i = 0; i < (*g_m)->nr_statii; i++)
	{
		free((*g_c)[i]);
	}
	free((*g_m));
	free((*g_c));
}

int main(int argc, char const *argv[])
{
	FILE *fisier_date, *fisier_rezultate;
	fisier_date = fopen(argv[1], "rt");
	fisier_rezultate = fopen(argv[2], "wt");

	Graf_Metrou *g_metrou;
	Graf_Clienti **g_clienti;
	Statie_Metrou *statie;

	citire_date(fisier_date, &g_metrou, &g_clienti, &statie);
	rezolvare_cerinte(fisier_date, fisier_rezultate, g_metrou, g_clienti, statie);

	fclose(fisier_date);
	fclose(fisier_rezultate);

	eliberare_memorie(&g_metrou, &g_clienti, &statie);
	return 0;
}