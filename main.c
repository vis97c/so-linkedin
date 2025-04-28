#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char filename[] = "data.csv";
    FILE *file;
    char buffer[1024];
    char input[32];
    int line_number;

    while (1) {
        printf("Escribe el numero de la linea (o 'c' para salir): ");

        if (!fgets(input, sizeof(input), stdin)) {
            printf("Error leyendo input.\n");
            continue;
        }

        // Remove trailing newline
        input[strcspn(input, "\n")] = '\0';

        if (input[0] == 'c' || input[0] == 'C') {
            printf("Saliendo...\n");
            break;
        }

        // Try to parse input as a line number
        char *endptr;
        line_number = strtol(input, &endptr, 10);

        if (endptr == input || line_number < 1) {
            fprintf(stderr, "Numero de linea invalido.\n");
            continue;
        }

        file = fopen(filename, "r");

        if (!file) {
            perror("No se pudo abrir el archivo");
            break;
        }

        // Skip the first line (header)
        if (!fgets(buffer, sizeof(buffer), file)) {
            fprintf(stderr, "El archivo esta vacio o no tiene encabezado.\n");
            fclose(file);
            continue;
        }
        int current_line = 1;
        int found = 0;

        while (fgets(buffer, sizeof(buffer), file)) {
            if (current_line == line_number) {
                printf("Linea %d: %s", line_number, buffer);
                found = 1;
                break;
            }
            current_line++;
        }

        if (!found) {
            fprintf(stderr, "La linea %d no existe en %s.\n", line_number, filename);
        }

        fclose(file);
    }

    return 0;
}