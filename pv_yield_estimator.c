#include <stdio.h>

/* ========================================================= */
/*                                                           */
/*   File   : pv_yield_estimator.c                           */
/*   Topic: Solar Power - Photovoltaic Planning Tool         */
/*                                                           */
/*   Developed by: Oscar Matallana                           */
/*                                                           */
/*   GitHub : github.com/oscarmatallana                      */
/*   LinkedIn: linkedin.com/in/matallana                     */
/*                                                           */
/*   Description:                                            */
/*   Interactive multilingual photovoltaic engineering       */
/*   tool using beginner-friendly C and realistic            */
/*   engineering assumptions.                                */
/*                                                           */
/*   Supported Languages:                                    */
/*   - English                                               */
/*   - Español                                               */
/*   - Deutsch                                               */
/*                                                           */
/* ========================================================= */

#define ENGLISH 0
#define SPANISH 1
#define GERMAN 2

void	clear_input_buffer(void)
{
	char	c;

	while ((c = getchar()) != '\n' && c != EOF)
		;
}

int	select_language(void)
{
	int	language;

	printf("==================================================\n");
	printf("PV YIELD ESTIMATOR\n");
	printf("==================================================\n\n");

	printf("Select language / Seleccione idioma ");
	printf("/ Sprache wählen\n\n");

	printf("1. English\n");
	printf("2. Español\n");
	printf("3. Deutsch\n\n");

	language = 0;

	while (language < 1 || language > 3)
	{
		printf("Option: ");

		if (scanf("%d", &language) != 1)
		{
			printf("Invalid input.\n");
			clear_input_buffer();
			language = 0;
		}
	}

	return (language - 1);
}

void	print_header(int language)
{
	printf("\n==================================================\n");
	printf("=============== PV YIELD ESTIMATOR ===============\n");
	printf("==================================================\n\n");

	if (language == ENGLISH)
	{
		printf("Developed by Oscar Matallana\n");
		printf("Engineering-Systems Project\n\n");

		printf("Educational photovoltaic engineering simulator.\n");
		printf("Estimate energy production and yearly savings\n");
		printf("using realistic engineering assumptions.\n\n");

		printf("IMPORTANT:\n");
		printf("Use decimal point for decimal numbers.\n");
		printf("Example: 0.85\n\n");
	}

	else if (language == SPANISH)
	{
		printf("Desarrollado por Oscar Matallana\n");
		printf("Proyecto Engineering-Systems\n\n");

		printf("Simulador educativo de ingeniería fotovoltaica.\n");
		printf("Estime producción energética y ahorro anual\n");
		printf("usando supuestos realistas de ingeniería.\n\n");

		printf("IMPORTANTE:\n");
		printf("Use punto decimal para números decimales.\n");
		printf("Ejemplo: 0.85\n\n");
	}

	else if (language == GERMAN)
	{
		printf("Entwickelt von Oscar Matallana\n");
		printf("Engineering-Systems Projekt\n\n");

		printf("Pädagogischer photovoltaischer Simulator.\n");
		printf("Schätzen Sie Energieproduktion und jährliche\n");
		printf("Einsparungen mit realistischen Annahmen.\n\n");

		printf("WICHTIG:\n");
		printf("Verwenden Sie einen Punkt für Dezimalzahlen.\n");
		printf("Beispiel: 0.85\n\n");
	}
}

float	get_valid_float(float min,
			float max,
			char *message,
			int language)
{
	float	value;
	int		valid;

	valid = 0;

	while (valid == 0)
	{
		printf("%s", message);

		if (scanf("%f", &value) != 1)
		{
			if (language == ENGLISH)
				printf("Error: Numbers only.\n\n");

			else if (language == SPANISH)
				printf("Error: Solo números.\n\n");

			else if (language == GERMAN)
				printf("Fehler: Nur Zahlen erlaubt.\n\n");

			clear_input_buffer();
		}

		else if (value < min || value > max)
		{
			if (language == ENGLISH)
			{
				printf("Error: Value must be between ");
				printf("%.2f and %.2f.\n\n",
					min, max);
			}

			else if (language == SPANISH)
			{
				printf("Error: El valor debe estar ");
				printf("entre %.2f y %.2f.\n\n",
					min, max);
			}

			else if (language == GERMAN)
			{
				printf("Fehler: Wert muss zwischen ");
				printf("%.2f und %.2f liegen.\n\n",
					min, max);
			}
		}

		else
			valid = 1;
	}

	return (value);
}

int	get_valid_int(int min,
		int max,
		char *message,
		int language)
{
	int	value;
	int	valid;

	valid = 0;

	while (valid == 0)
	{
		printf("%s", message);

		if (scanf("%d", &value) != 1)
		{
			if (language == ENGLISH)
				printf("Error: Numbers only.\n\n");

			else if (language == SPANISH)
				printf("Error: Solo números.\n\n");

			else if (language == GERMAN)
				printf("Fehler: Nur Zahlen erlaubt.\n\n");

			clear_input_buffer();
		}

		else if (value < min || value > max)
		{
			if (language == ENGLISH)
				printf("Error: Invalid option.\n\n");

			else if (language == SPANISH)
				printf("Error: Opción inválida.\n\n");

			else if (language == GERMAN)
				printf("Fehler: Ungültige Option.\n\n");
		}

		else
			valid = 1;
	}

	return (value);
}

void	print_mode_information(int language)
{
	if (language == ENGLISH)
	{
		printf("1. QUICK ESTIMATION\n");
		printf("- Fast photovoltaic estimation\n");
		printf("- Approximate duration: 1-2 minutes\n\n");

		printf("2. ADVANCED ENGINEERING ESTIMATION\n");
		printf("- Detailed engineering simulation\n");
		printf("- Includes roof, shading and comparison\n");
		printf("- Approximate duration: 4-7 minutes\n\n");
	}

	else if (language == SPANISH)
	{
		printf("1. ESTIMACIÓN RÁPIDA\n");
		printf("- Estimación fotovoltaica rápida\n");
		printf("- Duración aproximada: 1-2 minutos\n\n");

		printf("2. ESTIMACIÓN AVANZADA\n");
		printf("- Simulación detallada de ingeniería\n");
		printf("- Incluye techo, sombras y comparación\n");
		printf("- Duración aproximada: 4-7 minutos\n\n");
	}

	else if (language == GERMAN)
	{
		printf("1. SCHNELLE SCHÄTZUNG\n");
		printf("- Schnelle photovoltaische Schätzung\n");
		printf("- Geschätzte Dauer: 1-2 Minuten\n\n");

		printf("2. ERWEITERTE SIMULATION\n");
		printf("- Detaillierte technische Simulation\n");
		printf("- Mit Dach, Verschattung und Vergleich\n");
		printf("- Geschätzte Dauer: 4-7 Minuten\n\n");
	}
}

float	select_irradiation_value(int language)
{
	int		option;
	float	irradiation;

	irradiation = 0;

	while (irradiation == 0)
	{
		printf("\n==================================================\n");

		if (language == ENGLISH)
			printf("SOLAR IRRADIATION MENU\n");

		else if (language == SPANISH)
			printf("MENÚ DE IRRADIACIÓN SOLAR\n");

		else if (language == GERMAN)
			printf("SOLARSTRAHLUNGS-MENÜ\n");

		printf("==================================================\n\n");

		if (language == ENGLISH)
		{
			printf("1. Berlin -> 1100\n");
			printf("2. Madrid -> 1900\n");
			printf("3. Bogota -> 1450\n");
			printf("4. Cartagena -> 1950\n");
			printf("5. Phoenix -> 2300\n");
			printf("6. Riyadh -> 2400\n");
			printf("7. Tokyo -> 1450\n");
			printf("8. Sydney -> 1800\n");
			printf("9. Custom value\n\n");
		}

		else if (language == SPANISH)
		{
			printf("1. Berlín -> 1100\n");
			printf("2. Madrid -> 1900\n");
			printf("3. Bogotá -> 1450\n");
			printf("4. Cartagena -> 1950\n");
			printf("5. Phoenix -> 2300\n");
			printf("6. Riad -> 2400\n");
			printf("7. Tokio -> 1450\n");
			printf("8. Sídney -> 1800\n");
			printf("9. Valor personalizado\n\n");
		}

		else if (language == GERMAN)
		{
			printf("1. Berlin -> 1100\n");
			printf("2. Madrid -> 1900\n");
			printf("3. Bogotá -> 1450\n");
			printf("4. Cartagena -> 1950\n");
			printf("5. Phoenix -> 2300\n");
			printf("6. Riad -> 2400\n");
			printf("7. Tokio -> 1450\n");
			printf("8. Sydney -> 1800\n");
			printf("9. Benutzerdefinierter Wert\n\n");
		}

		option = get_valid_int(1, 9,
				"> ",
				language);

		if (option == 1)
			irradiation = 1100;

		else if (option == 2)
			irradiation = 1900;

		else if (option == 3)
			irradiation = 1450;

		else if (option == 4)
			irradiation = 1950;

		else if (option == 5)
			irradiation = 2300;

		else if (option == 6)
			irradiation = 2400;

		else if (option == 7)
			irradiation = 1450;

		else if (option == 8)
			irradiation = 1800;

		else if (option == 9)
		{
			if (language == ENGLISH)
			{
				irradiation = get_valid_float(
						500,
						3000,
						"Enter irradiation value: ",
						language);
			}

			else if (language == SPANISH)
			{
				irradiation = get_valid_float(
						500,
						3000,
						"Ingrese irradiación: ",
						language);
			}

			else if (language == GERMAN)
			{
				irradiation = get_valid_float(
						500,
						3000,
						"Geben Sie Strahlung ein: ",
						language);
			}
		}
	}

	return (irradiation);
}

void	run_quick_mode(int language)
{
	float	roof_area;
	float	irradiation;
	float	electricity_price;
	float	pr;
	float	installed_power;
	float	ideal_yield;
	float	adjusted_yield;
	float	savings;

	if (language == ENGLISH)
		printf("\nQUICK ESTIMATION MODE\n\n");

	else if (language == SPANISH)
		printf("\nMODO DE ESTIMACIÓN RÁPIDA\n\n");

	else if (language == GERMAN)
		printf("\nSCHNELLE SCHÄTZUNG\n\n");

	if (language == ENGLISH)
	{
		roof_area = get_valid_float(
				1,
				1000,
				"Enter roof area in m²: ",
				language);
	}

	else if (language == SPANISH)
	{
		roof_area = get_valid_float(
				1,
				1000,
				"Ingrese área del techo en m²: ",
				language);
	}

	else if (language == GERMAN)
	{
		roof_area = get_valid_float(
				1,
				1000,
				"Geben Sie Dachfläche in m² ein: ",
				language);
	}

	irradiation = select_irradiation_value(language);

	electricity_price = get_valid_float(
			0.05,
			1.00,
			"\nElectricity price: ",
			language);

	pr = get_valid_float(
			0.75,
			0.95,
			"\nPR (0.75 - 0.95): ",
			language);

	installed_power = roof_area * 0.22;

	ideal_yield = roof_area
		* irradiation
		* 0.22;

	adjusted_yield = ideal_yield
		* pr
		* 0.95;

	savings = adjusted_yield
		* electricity_price;

	printf("\n==================================================\n");

	if (language == ENGLISH)
		printf("RESULTS\n");

	else if (language == SPANISH)
		printf("RESULTADOS\n");

	else if (language == GERMAN)
		printf("ERGEBNISSE\n");

	printf("==================================================\n\n");

	printf("Installed capacity: %.2f kWp\n",
		installed_power);

	printf("Ideal yearly yield: %.0f kWh/year\n",
		ideal_yield);

	printf("Adjusted yearly yield: %.0f kWh/year\n",
		adjusted_yield);

	printf("Estimated yearly savings: %.2f\n",
		savings);
}

int	main(void)
{
	int	language;
	int	mode;

	language = select_language();

	print_header(language);

	print_mode_information(language);

	mode = get_valid_int(
			1,
			2,
			"> ",
			language);

	if (mode == 1)
		run_quick_mode(language);

	printf("\n==================================================\n");

	if (language == ENGLISH)
		printf("Thank you for using PV Yield Estimator.\n");

	else if (language == SPANISH)
		printf("Gracias por usar PV Yield Estimator.\n");

	else if (language == GERMAN)
		printf("Vielen Dank für die Nutzung des Programms.\n");

	printf("==================================================\n");

	return (0);
}
