#include <stdio.h>

int main()
{
	unsigned int num_casos;
	scanf("%d\n", &num_casos);

	unsigned int i, j, k;
	for (i = 0; i < num_casos; ++i)
	{
		unsigned int num_pctes;
		scanf("%d\n", &num_pctes);

		unsigned int brinquedos_pctes[num_pctes];
		unsigned int peso_pctes[num_pctes];
		for (j = 0; j < num_pctes; ++j)
			scanf("%d %d\n", &brinquedos_pctes[j], &peso_pctes[j]);

		unsigned int brinquedos_saco[num_pctes+1][51];
		unsigned int peso_saco[num_pctes+1][51];
		unsigned int pctes_saco[num_pctes+1][51];

		// CASOS BASE
		for (j = 0; j < num_pctes; ++j)
		{
			brinquedos_saco[j][0] = 0;
			peso_saco[j][0] = 0;
			pctes_saco[j][0] = 0;
		}
		for (k = 0; k < 51; ++k)
		{
			brinquedos_saco[0][k] = 0;
			peso_saco[0][k] = 0;
			pctes_saco[0][k] = 0;
		}

		for (j = 1; j <= num_pctes; ++j)
		{
			for (k = 1; k < 51; ++k)
			{
				if (peso_pctes[j-1] > k)
				{
					brinquedos_saco[j][k] = brinquedos_saco[j-1][k];
					peso_saco[j][k] = peso_saco[j-1][k];
					pctes_saco[j][k] = pctes_saco[j-1][k];
				}
				else
				{
					if (brinquedos_saco[j-1][k] < (brinquedos_saco[j-1][k-peso_pctes[j-1]] + brinquedos_pctes[j-1]))
					{
						brinquedos_saco[j][k] = brinquedos_saco[j-1][k-peso_pctes[j-1]] + brinquedos_pctes[j-1];
						peso_saco[j][k] = peso_saco[j-1][k-peso_pctes[j-1]] + peso_pctes[j-1];
						pctes_saco[j][k] = pctes_saco[j-1][k-peso_pctes[j-1]] + 1;
					}
					else
					{
						brinquedos_saco[j][k] = brinquedos_saco[j-1][k];
						peso_saco[j][k] = peso_saco[j-1][k];
						pctes_saco[j][k] = pctes_saco[j-1][k];
					}
				}
			}
		}

		printf("%d brinquedos\nPeso: %d kg\nsobra(m) %d pacote(s)\n\n", brinquedos_saco[num_pctes][50], peso_saco[num_pctes][50], num_pctes - pctes_saco[num_pctes][50]);
	}
}
