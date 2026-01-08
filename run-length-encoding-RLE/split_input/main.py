import sys


def read_input_file(filename):
    """
    Lê o arquivo de entrada original (SEM IDS).
    Formato:
    TOTAL
    TAMANHO DADO DADO...
    """
    try:
        with open(filename, "r") as f:
            tokens = f.read().split()

        if not tokens:
            return []

        iterator = iter(tokens)

        try:
            total_inputs = int(next(iterator))
        except StopIteration:
            return []

        cases = []
        for _ in range(total_inputs):
            try:
                # Lê o TAMANHO
                input_len = int(next(iterator))

                # Lê os DADOS
                case_data = []
                for _ in range(input_len):
                    case_data.append(next(iterator))
                cases.append(case_data)

            except StopIteration:
                break
            except ValueError:
                print("Erro de parsing: arquivo de entrada mal formatado.")
                sys.exit(1)

        return cases
    except FileNotFoundError:
        print(f"Erro: Arquivo {filename} não encontrado.")
        sys.exit(1)


def filter_and_renumber(input_path, gabarito_path):
    # 1. Carrega todas as entradas originais (indexadas de 0 a N)
    all_inputs = read_input_file(input_path)
    if not all_inputs:
        print("Nenhuma entrada lida.")
        return

    # Listas para guardar tuplas (id_original, sufixo_do_gabarito)
    rle_entries = []
    huff_entries = []

    # 2. Lê e processa o gabarito
    try:
        with open(gabarito_path, "r") as f:
            lines = f.readlines()

        for line in lines:
            stripped = line.strip()
            if not stripped:
                continue

            # Formato: "9241->RLE(0.09%)=..."
            try:
                parts = stripped.split("->")
                original_id = int(parts[0])
                suffix = "->".join(
                    parts[1:]
                )  # Pega o resto da linha (RLE... ou HUF...)

                if "RLE" in suffix:
                    rle_entries.append((original_id, suffix))
                else:
                    huff_entries.append((original_id, suffix))
            except ValueError:
                continue

    except FileNotFoundError:
        print(f"Erro: Arquivo {gabarito_path} não encontrado.")
        sys.exit(1)

    # 3. ORDENAR PELO ID ORIGINAL
    # Isso resolve o problema da "ordem de execução" das threads.
    # Garante que processamos do menor índice para o maior.
    rle_entries.sort(key=lambda x: x[0])
    huff_entries.sort(key=lambda x: x[0])

    # 4. Função para gravar os arquivos renumerados (0, 1, 2...)
    def write_files(prefix, entries):
        input_filename = f"{prefix}.input"
        output_filename = f"{prefix}.output"

        print(
            f"Gerando {input_filename} e {output_filename} com {len(entries)} casos..."
        )

        with open(input_filename, "w") as f_in, open(output_filename, "w") as f_out:
            # Cabeçalho do input (total de casos)
            f_in.write(f"{len(entries)}\n")

            # new_id começa de 0 automaticamente pelo enumerate
            for new_id, (original_id, suffix) in enumerate(entries):
                # --- ESCREVENDO O OUTPUT ---
                # Recomeça a contagem: 0->..., 1->...
                f_out.write(f"{new_id}->{suffix}\n")

                # --- ESCREVENDO O INPUT ---
                # Busca os dados originais usando o ID antigo
                if original_id < len(all_inputs):
                    data = all_inputs[original_id]
                    # Formato sem ID explícito: TAMANHO DADOS...
                    f_in.write(f"{len(data)} {' '.join(data)}\n")
                else:
                    print(
                        f"ERRO CRÍTICO: ID {original_id} no gabarito não existe na entrada!"
                    )

    # Gera os arquivos
    write_files("rle", rle_entries)
    write_files("huff", huff_entries)

    print("\nPronto! Arquivos gerados com contagem reiniciada (0, 1, 2...).")


if __name__ == "__main__":
    # Ajuste os nomes dos arquivos aqui se necessário
    ARQUIVO_ENTRADA = "compressao.input"
    ARQUIVO_GABARITO = "gabarito.out"

    filter_and_renumber(ARQUIVO_ENTRADA, ARQUIVO_GABARITO)
