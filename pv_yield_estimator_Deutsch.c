#include <stdio.h>

/* ========================================================= */
/*                                                           */
/*   Datei  : pv_yield_estimator_de.c                        */
/*   Projekt: PV-Planungstool                                */
/*                                                           */
/*   Entwickelt von: Oscar Matallana                         */
/*                                                           */
/*   Beschreibung:                                           */
/*   Pädagogisches Werkzeug zur Planung und                  */
/*   Ertragsabschätzung von Photovoltaikanlagen              */
/*   mit realistischen ingenieurtechnischen                  */
/*   Annahmen und einsteigerfreundlichem C-Code.             */
/*                                                           */
/* ========================================================= */

#define QUICK_MODE 1
#define ADVANCED_MODE 2

typedef struct s_result
{
	float	roof_area;
	float	irradiation;
	float	pr;
	float	installed_power;
	float	adjusted_yield;
	float	yearly_savings;
}	t_result;

void	clear_input_buffer(void)
{
	char	c;

	while ((c = getchar()) != '\n' && c != EOF)
		;
}

int	get_valid_int(int min, int max, char *message)
{
	int	value;
	int	valid;

	valid = 0;

	while (valid == 0)
	{
		printf("%s", message);

		if (scanf("%d", &value) != 1)
		{
			printf("Fehler: Nur Zahlen erlaubt.\n\n");
			clear_input_buffer();
		}
		else if (value < min || value > max)
		{
			printf("Fehler: Der Wert muss zwischen ");
			printf("%d und %d liegen.\n\n", min, max);
			clear_input_buffer();
		}
		else
		{
			clear_input_buffer();
			valid = 1;
		}
	}
	return (value);
}

float	get_valid_float(float min,
			float max,
			char *message)
{
	float	value;
	int		valid;

	valid = 0;

	while (valid == 0)
	{
		printf("%s", message);

		if (scanf("%f", &value) != 1)
		{
			printf("Fehler: Nur Zahlen erlaubt.\n\n");
			clear_input_buffer();
		}
		else if (value < min || value > max)
		{
			printf("Fehler: Der Wert muss zwischen ");
			printf("%.2f und %.2f liegen.\n\n",
				min, max);
			clear_input_buffer();
		}
		else
		{
			clear_input_buffer();
			valid = 1;
		}
	}
	return (value);
}

void	print_header(void)
{
	printf("==================================================\n");
	printf("=============== PV-ERTRAGSRECHNER ================\n");
	printf("==================================================\n\n");

	printf("Entwickelt von Oscar Matallana\n");
	printf("PV-Planungstool\n\n");

	printf("Pädagogische Photovoltaik-Software\n");
	printf("zur Planung und Abschätzung von Solarenergie.\n\n");

	printf("WICHTIG:\n");
	printf("- Verwenden Sie einen Punkt für Dezimalzahlen\n");
	printf("- Beispiel: 0.85\n\n");
}

void	print_mode_information(void)
{
	printf("==================================================\n");
	printf("================ BERECHNUNGSMODI =================\n");
	printf("==================================================\n\n");

	printf("1. SCHNELLE SCHÄTZUNG\n");
	printf("- Schnelle Photovoltaik-Abschätzung\n");
	printf("- Ungefähre Dauer: 1-2 Minuten\n\n");

	printf("2. ERWEITERTE INGENIEURTECHNISCHE SCHÄTZUNG\n");
	printf("- Detaillierte ingenieurtechnische Simulation\n");
	printf("- Einschließlich Ausrichtung und Verschattung\n");
	printf("- Ungefähre Dauer: 4-7 Minuten\n\n");
}

void	print_region_menu(void)
{
	printf("\n==================================================\n");
	printf("================ REGION WÄHLEN ===================\n");
	printf("==================================================\n\n");

	printf("1. Nordamerika\n");
	printf("2. Südamerika\n");
	printf("3. Europa\n");
	printf("4. Afrika\n");
	printf("5. Asien\n");
	printf("6. Ozeanien\n\n");
}

void	print_region_cities(int region)
{
	if (region == 1)
	{
		printf("\n================ NORDAMERIKA =====================\n\n");

		printf("1. Toronto, Kanada -> 1200 kWh/m²/Jahr\n");
		printf("2. Vancouver, Kanada -> 1100 kWh/m²/Jahr\n");
		printf("3. Montreal, Kanada -> 1150 kWh/m²/Jahr\n");

		printf("4. Phoenix, USA -> 2300 kWh/m²/Jahr\n");
		printf("5. Los Angeles, USA -> 1900 kWh/m²/Jahr\n");
		printf("6. New York, USA -> 1400 kWh/m²/Jahr\n");

		printf("7. Mexiko-Stadt, Mexiko -> 1900 kWh/m²/Jahr\n");
		printf("8. Monterrey, Mexiko -> 2100 kWh/m²/Jahr\n");
		printf("9. Guadalajara, Mexiko -> 2000 kWh/m²/Jahr\n\n");
	}
	else if (region == 2)
	{
		printf("\n================ SÜDAMERIKA ======================\n\n");

		printf("1. Bogotá, Kolumbien -> 1450 kWh/m²/Jahr\n");
		printf("2. Cartagena, Kolumbien -> 1950 kWh/m²/Jahr\n");
		printf("3. Medellín, Kolumbien -> 1550 kWh/m²/Jahr\n");
		printf("4. Cali, Kolumbien -> 1650 kWh/m²/Jahr\n");

		printf("5. São Paulo, Brasilien -> 1700 kWh/m²/Jahr\n");
		printf("6. Rio de Janeiro, Brasilien -> 1800 kWh/m²/Jahr\n");
		printf("7. Salvador, Brasilien -> 2000 kWh/m²/Jahr\n");

		printf("8. Buenos Aires, Argentinien -> 1600 kWh/m²/Jahr\n");
		printf("9. Córdoba, Argentinien -> 1800 kWh/m²/Jahr\n");
		printf("10. Mendoza, Argentinien -> 2100 kWh/m²/Jahr\n\n");
	}
	else if (region == 3)
	{
		printf("\n==================== EUROPA ======================\n\n");

		printf("1. Berlin, Deutschland -> 1100 kWh/m²/Jahr\n");
		printf("2. München, Deutschland -> 1190 kWh/m²/Jahr\n");
		printf("3. Hamburg, Deutschland -> 1050 kWh/m²/Jahr\n");

		printf("4. Madrid, Spanien -> 1900 kWh/m²/Jahr\n");
		printf("5. Sevilla, Spanien -> 2100 kWh/m²/Jahr\n");
		printf("6. Barcelona, Spanien -> 1750 kWh/m²/Jahr\n");

		printf("7. Stockholm, Schweden -> 1000 kWh/m²/Jahr\n");
		printf("8. Göteborg, Schweden -> 980 kWh/m²/Jahr\n");
		printf("9. Malmö, Schweden -> 1050 kWh/m²/Jahr\n\n");
	}
	else if (region == 4)
	{
		printf("\n==================== AFRIKA ======================\n\n");

		printf("1. Casablanca, Marokko -> 2000 kWh/m²/Jahr\n");
		printf("2. Marrakesch, Marokko -> 2200 kWh/m²/Jahr\n");
		printf("3. Rabat, Marokko -> 1900 kWh/m²/Jahr\n");

		printf("4. Lagos, Nigeria -> 1800 kWh/m²/Jahr\n");
		printf("5. Abuja, Nigeria -> 2000 kWh/m²/Jahr\n");
		printf("6. Kano, Nigeria -> 2200 kWh/m²/Jahr\n");

		printf("7. Kapstadt, Südafrika -> 2100 kWh/m²/Jahr\n");
		printf("8. Johannesburg, Südafrika -> 2200 kWh/m²/Jahr\n");
		printf("9. Durban, Südafrika -> 1800 kWh/m²/Jahr\n\n");
	}
	else if (region == 5)
	{
		printf("\n===================== ASIEN ======================\n\n");

		printf("1. Riad, Saudi-Arabien -> 2400 kWh/m²/Jahr\n");
		printf("2. Dschidda, Saudi-Arabien -> 2300 kWh/m²/Jahr\n");
		printf("3. Dammam, Saudi-Arabien -> 2350 kWh/m²/Jahr\n");

		printf("4. Tokio, Japan -> 1450 kWh/m²/Jahr\n");
		printf("5. Osaka, Japan -> 1500 kWh/m²/Jahr\n");
		printf("6. Sapporo, Japan -> 1200 kWh/m²/Jahr\n");

		printf("7. Peking, China -> 1700 kWh/m²/Jahr\n");
		printf("8. Shanghai, China -> 1400 kWh/m²/Jahr\n");
		printf("9. Shenzhen, China -> 1500 kWh/m²/Jahr\n");

		printf("10. Bangkok, Thailand -> 1800 kWh/m²/Jahr\n");
		printf("11. Seoul, Südkorea -> 1350 kWh/m²/Jahr\n");
		printf("12. Taipeh, Taiwan -> 1600 kWh/m²/Jahr\n");

		printf("13. Manila, Philippinen -> 1900 kWh/m²/Jahr\n");
		printf("14. Jakarta, Indonesien -> 1700 kWh/m²/Jahr\n");
		printf("15. Neu-Delhi, Indien -> 2100 kWh/m²/Jahr\n\n");
	}
	else if (region == 6)
	{
		printf("\n==================== OZEANIEN ====================\n\n");

		printf("1. Sydney, Australien -> 1800 kWh/m²/Jahr\n");
		printf("2. Perth, Australien -> 2200 kWh/m²/Jahr\n");
		printf("3. Melbourne, Australien -> 1700 kWh/m²/Jahr\n");

		printf("4. Auckland, Neuseeland -> 1400 kWh/m²/Jahr\n");
		printf("5. Wellington, Neuseeland -> 1350 kWh/m²/Jahr\n");
		printf("6. Christchurch, Neuseeland -> 1450 kWh/m²/Jahr\n\n");
	}
}

int	get_city_limit(int region)
{
	if (region == 1)
		return (9);
	else if (region == 2)
		return (10);
	else if (region == 3)
		return (9);
	else if (region == 4)
		return (9);
	else if (region == 5)
		return (15);
	else if (region == 6)
		return (6);
	return (0);
}

float	get_city_irradiation(int region, int city)
{
	if (region == 1)
	{
		float values[9] = {
			1200, 1100, 1150,
			2300, 1900, 1400,
			1900, 2100, 2000};

		return (values[city - 1]);
	}
	else if (region == 2)
	{
		float values[10] = {
			1450, 1950, 1550, 1650,
			1700, 1800, 2000,
			1600, 1800, 2100};

		return (values[city - 1]);
	}
	else if (region == 3)
	{
		float values[9] = {
			1100, 1190, 1050,
			1900, 2100, 1750,
			1000, 980, 1050};

		return (values[city - 1]);
	}
	else if (region == 4)
	{
		float values[9] = {
			2000, 2200, 1900,
			1800, 2000, 2200,
			2100, 2200, 1800};

		return (values[city - 1]);
	}
	else if (region == 5)
	{
		float values[15] = {
			2400, 2300, 2350,
			1450, 1500, 1200,
			1700, 1400, 1500,
			1800, 1350, 1600,
			1900, 1700, 2100};

		return (values[city - 1]);
	}
	else if (region == 6)
	{
		float values[6] = {
			1800, 2200, 1700,
			1400, 1350, 1450};

		return (values[city - 1]);
	}
	return (0);
}

float	select_irradiation_value(void)
{
	int		menu;
	int		region;
	int		city;
	int		city_limit;
	float	irradiation;

	printf("\n==================================================\n");
	printf("============= SOLARE EINSTRAHLUNG ================\n");
	printf("==================================================\n\n");

	printf("1. Schnelle Voreinstellungen nach Region\n");
	printf("2. Benutzerdefinierten Einstrahlungswert eingeben\n\n");

	menu = get_valid_int(1, 2, "Option: ");

	if (menu == 2)
	{
		irradiation = get_valid_float(
				500,
				3000,
				"Solare Einstrahlung (kWh/m²/Jahr): ");
		return (irradiation);
	}

	print_region_menu();

	region = get_valid_int(1, 6, "Region: ");

	print_region_cities(region);

	city_limit = get_city_limit(region);

	city = get_valid_int(1, city_limit, "Stadt: ");

	irradiation = get_city_irradiation(region, city);

	return (irradiation);
}

void	print_electricity_examples(void)
{
	printf("==================================================\n");
	printf("BEISPIELE FÜR STROMPREISE IM WOHNBEREICH\n");
	printf("==================================================\n\n");

	printf("Deutschland: 0.30 - 0.45 EUR/kWh\n");
	printf("USA:         0.12 - 0.25 USD/kWh\n");
	printf("China:       0.08 - 0.15 CNY/kWh\n\n");

	printf("Typischer realistischer Bereich für Haushalte:\n");
	printf("0.05 - 0.60 Währung/kWh\n\n");
}

float	get_orientation_factor(void)
{
	int		option;
	float	factor;

	printf("==================================================\n");
	printf("================ DACHAUSRICHTUNG =================\n");
	printf("==================================================\n\n");

	printf("1. Südausrichtung\n");
	printf("2. Südost / Südwest\n");
	printf("3. Ost / West\n");
	printf("4. Nordausrichtung\n\n");

	option = get_valid_int(1, 4, "Option: ");

	factor = 1.0;

	if (option == 1)
		factor = 1.00;
	else if (option == 2)
		factor = 0.95;
	else if (option == 3)
		factor = 0.85;
	else if (option == 4)
		factor = 0.65;

	return (factor);
}

float	get_shading_factor(void)
{
	int		option;
	float	factor;

	printf("==================================================\n");
	printf("================ VERSCHATTUNG ====================\n");
	printf("==================================================\n\n");

	printf("1. Keine Verschattung\n");
	printf("2. Leichte Verschattung\n");
	printf("3. Mittlere Verschattung\n");
	printf("4. Starke Verschattung\n\n");

	option = get_valid_int(1, 4, "Option: ");

	factor = 1.0;

	if (option == 1)
		factor = 1.00;
	else if (option == 2)
		factor = 0.90;
	else if (option == 3)
		factor = 0.75;
	else if (option == 4)
		factor = 0.50;

	return (factor);
}

void	print_results(t_result result)
{
	printf("==================================================\n");
	printf("==================== ERGEBNISSE ==================\n");
	printf("==================================================\n\n");

	printf("Installierte PV-Leistung:\n");
	printf("%.2f kWp\n\n", result.installed_power);

	printf("Angepasster jährlicher Energieertrag:\n");
	printf("%.0f kWh/Jahr\n\n", result.adjusted_yield);

	printf("Geschätzte jährliche Stromkosteneinsparung:\n");
	printf("%.2f Währung/Jahr\n\n",
		result.yearly_savings);
}

void	print_comparison_table(t_result first,
				t_result second)
{
	printf("==================================================\n");
	printf("================ STANDORTVERGLEICH ===============\n");
	printf("==================================================\n\n");

	printf("%-25s %-15s %-15s\n",
		"Parameter",
		"Standort 1",
		"Standort 2");

	printf("--------------------------------------------------\n");

	printf("%-25s %-15.2f %-15.2f\n",
		"Dachfläche (m²)",
		first.roof_area,
		second.roof_area);

	printf("%-25s %-15.0f %-15.0f\n",
		"Einstrahlung",
		first.irradiation,
		second.irradiation);

	printf("%-25s %-15.2f %-15.2f\n",
		"Performance Ratio",
		first.pr,
		second.pr);

	printf("%-25s %-15.2f %-15.2f\n",
		"Installierte Leistung",
		first.installed_power,
		second.installed_power);

	printf("%-25s %-15.0f %-15.0f\n",
		"Angepasster Ertrag",
		first.adjusted_yield,
		second.adjusted_yield);

	printf("%-25s %-15.2f %-15.2f\n",
		"Jährliche Einsparung",
		first.yearly_savings,
		second.yearly_savings);

	printf("\n");
}

int	ask_repeat_program(void)
{
	int	option;

	printf("==================================================\n");
	printf("================ NÄCHSTE AKTION ==================\n");
	printf("==================================================\n\n");

	printf("1. Neue Berechnung\n");
	printf("2. Beenden\n\n");

	option = get_valid_int(1, 2, "Option: ");

	return (option);
}

int	ask_comparison(void)
{
	int	option;

	printf("==================================================\n");
	printf("================ VERGLEICHSMODUS =================\n");
	printf("==================================================\n\n");

	printf("Möchten Sie mit einem anderen Standort vergleichen?\n\n");

	printf("1. Ja\n");
	printf("2. Nein\n\n");

	option = get_valid_int(1, 2, "Option: ");

	return (option);
}

t_result	run_quick_mode(void)
{
	t_result	result;
	float		electricity_price;

	printf("==================================================\n");
	printf("================ SCHNELLE SCHÄTZUNG ==============\n");
	printf("==================================================\n\n");

	result.roof_area = get_valid_float(
			1,
			1000,
			"Nutzbare Dachfläche (m²): ");

	result.irradiation = select_irradiation_value();

	print_electricity_examples();

	electricity_price = get_valid_float(
			0.05,
			0.60,
			"Strompreis (Währung/kWh): ");

	printf("==================================================\n");
	printf("============= PERFORMANCE RATIO (PR) =============\n");
	printf("==================================================\n\n");

	printf("0.95 -> außergewöhnlich optimiertes System\n");
	printf("0.90 -> sehr gute moderne Installation\n");
	printf("0.85 -> realistisches gutes Wohnsystem\n");
	printf("0.80 -> durchschnittliches System\n");
	printf("0.75 -> deutliche Verluste\n\n");

	result.pr = get_valid_float(
			0.75,
			0.95,
			"Performance Ratio - PR (0.75 - 0.95): ");

	result.installed_power = result.roof_area * 0.22;

	result.adjusted_yield =
		result.roof_area
		* result.irradiation
		* 0.22
		* result.pr;

	result.yearly_savings =
		result.adjusted_yield
		* electricity_price;

	print_results(result);

	return (result);
}

t_result	run_advanced_mode(void)
{
	t_result	result;

	float	module_power;
	float	module_length;
	float	module_width;
	float	module_area;
	float	module_power_density;

	float	electricity_price;
	float	orientation_factor;
	float	shading_factor;

	printf("==================================================\n");
	printf("========== ERWEITERTER INGENIEURMODUS ============\n");
	printf("==================================================\n\n");

	module_power = get_valid_float(
			100,
			800,
			"Nennleistung des Moduls (Wp): ");

	module_length = get_valid_float(
			0.5,
			3.0,
			"Modullänge (m): ");

	module_width = get_valid_float(
			0.5,
			2.0,
			"Modulbreite (m): ");

	result.roof_area = get_valid_float(
			1,
			1000,
			"Nutzbare Dachfläche (m²): ");

	result.irradiation = select_irradiation_value();

	print_electricity_examples();

	electricity_price = get_valid_float(
			0.05,
			0.60,
			"Strompreis (Währung/kWh): ");

	printf("==================================================\n");
	printf("============= PERFORMANCE RATIO (PR) =============\n");
	printf("==================================================\n\n");

	printf("0.95 -> außergewöhnlich optimiertes System\n");
	printf("0.90 -> sehr gute moderne Installation\n");
	printf("0.85 -> realistisches gutes Wohnsystem\n");
	printf("0.80 -> durchschnittliches System\n");
	printf("0.75 -> deutliche Verluste\n\n");

	result.pr = get_valid_float(
			0.75,
			0.95,
			"Performance Ratio - PR (0.75 - 0.95): ");

	orientation_factor = get_orientation_factor();

	shading_factor = get_shading_factor();

	module_area = module_length * module_width;

	module_power_density =
		(module_power / 1000)
		/ module_area;

	result.installed_power =
		result.roof_area
		* module_power_density;

	result.adjusted_yield =
		result.roof_area
		* result.irradiation
		* module_power_density
		* result.pr
		* orientation_factor
		* shading_factor;

	result.yearly_savings =
		result.adjusted_yield
		* electricity_price;

	print_results(result);

	return (result);
}

int	main(void)
{
	int			mode;
	int			restart;
	int			comparison;

	t_result	first;
	t_result	second;

	restart = 1;

	while (restart == 1)
	{
		print_header();

		print_mode_information();

		mode = get_valid_int(
				1,
				2,
				"Modus auswählen: ");

		if (mode == QUICK_MODE)
			first = run_quick_mode();
		else
			first = run_advanced_mode();

		comparison = ask_comparison();

		if (comparison == 1)
		{
			printf("\nBERECHNUNG DES ZWEITEN STANDORTS\n");

			if (mode == QUICK_MODE)
				second = run_quick_mode();
			else
				second = run_advanced_mode();

			print_comparison_table(first,
					second);
		}

		restart = ask_repeat_program();

		printf("\n");
	}

	printf("==================================================\n");
	printf("Vielen Dank für die Nutzung des PV-Ertragsrechners.\n");
	printf("==================================================\n");

	return (0);
}