#include <stdio.h>

/* ========================================================= */
/*                                                           */
/*   File   : pv_yield_estimator_en.c                        */
/*   Project: PV Planning Tool                               */
/*                                                           */
/*   Developed by: Oscar Matallana                           */
/*                                                           */
/*   Description:                                            */
/*   Educational photovoltaic planning and yield             */
/*   estimation tool using realistic engineering             */
/*   assumptions and beginner-friendly C.                    */
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
			printf("Error: Numbers only.\n\n");
			clear_input_buffer();
		}
		else if (value < min || value > max)
		{
			printf("Error: Value must be between ");
			printf("%d and %d.\n\n", min, max);
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
			printf("Error: Numbers only.\n\n");
			clear_input_buffer();
		}
		else if (value < min || value > max)
		{
			printf("Error: Value must be between ");
			printf("%.2f and %.2f.\n\n",
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
	printf("=============== PV YIELD ESTIMATOR ===============\n");
	printf("==================================================\n\n");

	printf("Developed by Oscar Matallana\n");
	printf("PV Planning Tool\n\n");

	printf("Educational photovoltaic engineering software\n");
	printf("for solar energy planning and estimation.\n\n");

	printf("IMPORTANT:\n");
	printf("- Use decimal point for decimal numbers\n");
	printf("- Example: 0.85\n\n");
}

void	print_mode_information(void)
{
	printf("==================================================\n");
	printf("================= CALCULATION MODES ==============\n");
	printf("==================================================\n\n");

	printf("1. QUICK ESTIMATION\n");
	printf("- Fast photovoltaic estimation\n");
	printf("- Approximate duration: 1-2 minutes\n\n");

	printf("2. ADVANCED ENGINEERING ESTIMATION\n");
	printf("- Detailed engineering simulation\n");
	printf("- Includes orientation and shading\n");
	printf("- Approximate duration: 4-7 minutes\n\n");
}

void	print_region_menu(void)
{
	printf("\n==================================================\n");
	printf("=============== SELECT REGION ====================\n");
	printf("==================================================\n\n");

	printf("1. North America\n");
	printf("2. South America\n");
	printf("3. Europe\n");
	printf("4. Africa\n");
	printf("5. Asia\n");
	printf("6. Oceania\n\n");
}

void	print_region_cities(int region)
{
	if (region == 1)
	{
		printf("\n================ NORTH AMERICA ===================\n\n");

		printf("1. Toronto, Canada -> 1200 kWh/m²/year\n");
		printf("2. Vancouver, Canada -> 1100 kWh/m²/year\n");
		printf("3. Montreal, Canada -> 1150 kWh/m²/year\n");

		printf("4. Phoenix, USA -> 2300 kWh/m²/year\n");
		printf("5. Los Angeles, USA -> 1900 kWh/m²/year\n");
		printf("6. New York, USA -> 1400 kWh/m²/year\n");

		printf("7. Mexico City, Mexico -> 1900 kWh/m²/year\n");
		printf("8. Monterrey, Mexico -> 2100 kWh/m²/year\n");
		printf("9. Guadalajara, Mexico -> 2000 kWh/m²/year\n\n");
	}
	else if (region == 2)
	{
		printf("\n================ SOUTH AMERICA ===================\n\n");

		printf("1. Bogotá, Colombia -> 1450 kWh/m²/year\n");
		printf("2. Cartagena, Colombia -> 1950 kWh/m²/year\n");
		printf("3. Medellín, Colombia -> 1550 kWh/m²/year\n");
		printf("4. Cali, Colombia -> 1650 kWh/m²/year\n");

		printf("5. São Paulo, Brazil -> 1700 kWh/m²/year\n");
		printf("6. Rio de Janeiro, Brazil -> 1800 kWh/m²/year\n");
		printf("7. Salvador, Brazil -> 2000 kWh/m²/year\n");

		printf("8. Buenos Aires, Argentina -> 1600 kWh/m²/year\n");
		printf("9. Córdoba, Argentina -> 1800 kWh/m²/year\n");
		printf("10. Mendoza, Argentina -> 2100 kWh/m²/year\n\n");
	}
	else if (region == 3)
	{
		printf("\n==================== EUROPE ======================\n\n");

		printf("1. Berlin, Germany -> 1100 kWh/m²/year\n");
		printf("2. Munich, Germany -> 1190 kWh/m²/year\n");
		printf("3. Hamburg, Germany -> 1050 kWh/m²/year\n");

		printf("4. Madrid, Spain -> 1900 kWh/m²/year\n");
		printf("5. Seville, Spain -> 2100 kWh/m²/year\n");
		printf("6. Barcelona, Spain -> 1750 kWh/m²/year\n");

		printf("7. Stockholm, Sweden -> 1000 kWh/m²/year\n");
		printf("8. Gothenburg, Sweden -> 980 kWh/m²/year\n");
		printf("9. Malmö, Sweden -> 1050 kWh/m²/year\n\n");
	}
	else if (region == 4)
	{
		printf("\n==================== AFRICA ======================\n\n");

		printf("1. Casablanca, Morocco -> 2000 kWh/m²/year\n");
		printf("2. Marrakesh, Morocco -> 2200 kWh/m²/year\n");
		printf("3. Rabat, Morocco -> 1900 kWh/m²/year\n");

		printf("4. Lagos, Nigeria -> 1800 kWh/m²/year\n");
		printf("5. Abuja, Nigeria -> 2000 kWh/m²/year\n");
		printf("6. Kano, Nigeria -> 2200 kWh/m²/year\n");

		printf("7. Cape Town, South Africa -> 2100 kWh/m²/year\n");
		printf("8. Johannesburg, South Africa -> 2200 kWh/m²/year\n");
		printf("9. Durban, South Africa -> 1800 kWh/m²/year\n\n");
	}
	else if (region == 5)
	{
		printf("\n===================== ASIA =======================\n\n");

		printf("1. Riyadh, Saudi Arabia -> 2400 kWh/m²/year\n");
		printf("2. Jeddah, Saudi Arabia -> 2300 kWh/m²/year\n");
		printf("3. Dammam, Saudi Arabia -> 2350 kWh/m²/year\n");

		printf("4. Tokyo, Japan -> 1450 kWh/m²/year\n");
		printf("5. Osaka, Japan -> 1500 kWh/m²/year\n");
		printf("6. Sapporo, Japan -> 1200 kWh/m²/year\n");

		printf("7. Beijing, China -> 1700 kWh/m²/year\n");
		printf("8. Shanghai, China -> 1400 kWh/m²/year\n");
		printf("9. Shenzhen, China -> 1500 kWh/m²/year\n");

		printf("10. Bangkok, Thailand -> 1800 kWh/m²/year\n");
		printf("11. Seoul, South Korea -> 1350 kWh/m²/year\n");
		printf("12. Taipei, Taiwan -> 1600 kWh/m²/year\n");

		printf("13. Manila, Philippines -> 1900 kWh/m²/year\n");
		printf("14. Jakarta, Indonesia -> 1700 kWh/m²/year\n");
		printf("15. New Delhi, India -> 2100 kWh/m²/year\n\n");
	}
	else if (region == 6)
	{
		printf("\n==================== OCEANIA =====================\n\n");

		printf("1. Sydney, Australia -> 1800 kWh/m²/year\n");
		printf("2. Perth, Australia -> 2200 kWh/m²/year\n");
		printf("3. Melbourne, Australia -> 1700 kWh/m²/year\n");

		printf("4. Auckland, New Zealand -> 1400 kWh/m²/year\n");
		printf("5. Wellington, New Zealand -> 1350 kWh/m²/year\n");
		printf("6. Christchurch, New Zealand -> 1450 kWh/m²/year\n\n");
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
	printf("=========== SOLAR IRRADIATION MENU ===============\n");
	printf("==================================================\n\n");

	printf("1. Quick presets by region\n");
	printf("2. Enter custom irradiation value\n\n");

	menu = get_valid_int(1, 2, "Option: ");

	if (menu == 2)
	{
		irradiation = get_valid_float(
				500,
				3000,
				"Solar irradiation (kWh/m²/year): ");
		return (irradiation);
	}

	print_region_menu();

	region = get_valid_int(1, 6, "Region: ");

	print_region_cities(region);

	city_limit = get_city_limit(region);

	city = get_valid_int(1, city_limit, "City: ");

	irradiation = get_city_irradiation(region, city);

	return (irradiation);
}

void	print_electricity_examples(void)
{
	printf("\n==================================================\n");
	printf("EXAMPLE RESIDENTIAL ELECTRICITY PRICES\n");
	printf("==================================================\n\n");

	printf("Germany: 0.30 - 0.45 EUR/kWh\n");
	printf("USA:     0.12 - 0.25 USD/kWh\n");
	printf("China:   0.08 - 0.15 CNY/kWh\n\n");

	printf("Typical realistic residential range:\n");
	printf("0.05 - 0.60 currency/kWh\n\n");
}

float	get_orientation_factor(void)
{
	int		option;
	float	factor;

	printf("\n==================================================\n");
	printf("=============== ROOF ORIENTATION =================\n");
	printf("==================================================\n\n");

	printf("1. South-facing\n");
	printf("2. Southeast / Southwest\n");
	printf("3. East / West\n");
	printf("4. North-facing\n\n");

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

	printf("\n==================================================\n");
	printf("================ SHADING LEVEL ===================\n");
	printf("==================================================\n\n");

	printf("1. No shading\n");
	printf("2. Light shading\n");
	printf("3. Moderate shading\n");
	printf("4. Heavy shading\n\n");

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
	printf("\n==================================================\n");
	printf("==================== RESULTS =====================\n");
	printf("==================================================\n\n");

	printf("Installed PV Capacity:\n");
	printf("%.2f kWp\n\n", result.installed_power);

	printf("Adjusted Yearly Energy Yield:\n");
	printf("%.0f kWh/year\n\n", result.adjusted_yield);

	printf("Estimated Yearly Electricity Savings:\n");
	printf("%.2f currency/year\n\n",
		result.yearly_savings);
}

void	print_comparison_table(t_result first,
				t_result second)
{
	printf("\n==================================================\n");
	printf("================ LOCATION COMPARISON =============\n");
	printf("==================================================\n\n");

	printf("%-25s %-15s %-15s\n",
		"Parameter",
		"Location 1",
		"Location 2");

	printf("--------------------------------------------------\n");

	printf("%-25s %-15.2f %-15.2f\n",
		"Roof Area (m²)",
		first.roof_area,
		second.roof_area);

	printf("%-25s %-15.0f %-15.0f\n",
		"Irradiation",
		first.irradiation,
		second.irradiation);

	printf("%-25s %-15.2f %-15.2f\n",
		"Performance Ratio",
		first.pr,
		second.pr);

	printf("%-25s %-15.2f %-15.2f\n",
		"Installed Power",
		first.installed_power,
		second.installed_power);

	printf("%-25s %-15.0f %-15.0f\n",
		"Adjusted Yield",
		first.adjusted_yield,
		second.adjusted_yield);

	printf("%-25s %-15.2f %-15.2f\n",
		"Yearly Savings",
		first.yearly_savings,
		second.yearly_savings);

	printf("\n");
}

int	ask_repeat_program(void)
{
	int	option;

	printf("\n==================================================\n");
	printf("================ NEXT ACTION =====================\n");
	printf("==================================================\n\n");

	printf("1. New calculation\n");
	printf("2. Exit\n\n");

	option = get_valid_int(1, 2, "Option: ");

	return (option);
}

int	ask_comparison(void)
{
	int	option;

	printf("\n==================================================\n");
	printf("================ COMPARISON MODE =================\n");
	printf("==================================================\n\n");

	printf("Would you like to compare with another location?\n\n");

	printf("1. Yes\n");
	printf("2. No\n\n");

	option = get_valid_int(1, 2, "Option: ");

	return (option);
}

t_result	run_quick_mode(void)
{
	t_result	result;
	float		electricity_price;

	printf("\n==================================================\n");
	printf("================ QUICK ESTIMATION ================\n");
	printf("==================================================\n\n");

	result.roof_area = get_valid_float(
			1,
			1000,
			"Usable roof area (m²): ");

	result.irradiation = select_irradiation_value();

	print_electricity_examples();

	electricity_price = get_valid_float(
			0.05,
			0.60,
			"Electricity price (currency/kWh): ");

	printf("\n==================================================\n");
	printf("============= PERFORMANCE RATIO (PR) =============\n");
	printf("==================================================\n\n");

	printf("0.95 -> exceptionally optimized system\n");
	printf("0.90 -> very good modern installation\n");
	printf("0.85 -> realistic good residential system\n");
	printf("0.80 -> average system\n");
	printf("0.75 -> noticeable losses\n\n");

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

	printf("\n==================================================\n");
	printf("========== ADVANCED ENGINEERING MODE =============\n");
	printf("==================================================\n\n");

	module_power = get_valid_float(
			100,
			800,
			"Module nominal power (Wp): ");

	module_length = get_valid_float(
			0.5,
			3.0,
			"Module length (m): ");

	module_width = get_valid_float(
			0.5,
			2.0,
			"Module width (m): ");

	result.roof_area = get_valid_float(
			1,
			1000,
			"Usable roof area (m²): ");

	result.irradiation = select_irradiation_value();

	print_electricity_examples();

	electricity_price = get_valid_float(
			0.05,
			0.60,
			"Electricity price (currency/kWh): ");

	printf("\n==================================================\n");
	printf("============= PERFORMANCE RATIO (PR) =============\n");
	printf("==================================================\n\n");

	printf("0.95 -> exceptionally optimized system\n");
	printf("0.90 -> very good modern installation\n");
	printf("0.85 -> realistic good residential system\n");
	printf("0.80 -> average system\n");
	printf("0.75 -> noticeable losses\n\n");

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
				"Select mode: ");

		if (mode == QUICK_MODE)
			first = run_quick_mode();
		else
			first = run_advanced_mode();

		comparison = ask_comparison();

		if (comparison == 1)
		{
			printf("\nSECOND LOCATION CALCULATION\n");

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
	printf("Thank you for using PV Yield Estimator.\n");
	printf("==================================================\n");

	return (0);
}