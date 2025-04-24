"""Terminal assistant that uses Deepseek API to process commands."""

import os
import json
import argparse
from typing import Dict, Any
from openai import OpenAI
from openai._exceptions import OpenAIError
from dotenv import load_dotenv

load_dotenv()


def load_prompts() -> Dict[str, Any]:
    """Load prompts from the JSON file.
    
    Returns:
        Dictionary containing the prompts configuration.
        
    Raises:
        FileNotFoundError: If the prompts file is not found.
        json.JSONDecodeError: If the JSON file is invalid.
    """
    try:
        with open("prompts.json", "r", encoding="utf-8") as f:
            return json.load(f)
    except FileNotFoundError:
        raise FileNotFoundError("Arquivo prompts.json não encontrado.")
    except json.JSONDecodeError as e:
        raise ValueError(f"Erro ao decodificar o arquivo JSON: {e}")


def get_assistant_response(comando: str) -> str:
    """Get response from Deepseek API for a given command.
    
    Args:
        comando: The command or question to send to the assistant.
        
    Returns:
        The assistant's response as a string.
        
    Raises:
        OpenAIError: If there's an error communicating with the API.
        FileNotFoundError: If the prompts file is not found.
        ValueError: If there's an error with the prompts configuration.
    """
    try:
        prompts = load_prompts()
        system_prompt = prompts["prompts"]["terminal_assistant"]["system"]

        client = OpenAI(
            api_key=os.getenv("DEEPSEEK_API_KEY"),
            base_url="https://api.deepseek.com"
        )

        response = client.chat.completions.create(
            model="deepseek-chat",
            messages=[
                {
                    "role": "system",
                    "content": system_prompt
                },
                {"role": "user", "content": comando.strip()}
            ],
            max_tokens=int(os.getenv("ANSWER_MAX_TOKENS", 50))
        )

        return response.choices[0].message.content.strip()
    except OpenAIError as e:
        return f"Erro ao consultar a API: {e}"
    except (FileNotFoundError, ValueError) as e:
        return f"Erro: {str(e)}"


def main() -> None:
    """Main entry point for the terminal assistant."""
    parser = argparse.ArgumentParser(
        description="Comando para o assistente de terminal"
    )
    parser.add_argument(
        "comando",
        help="Comando a ser enviado para o assistente"
    )
    args = parser.parse_args()

    resposta = get_assistant_response(args.comando)
    print(f"Resposta do assistente: {resposta}")


if __name__ == "__main__":
    main()
