//
//  Pokedex
//  PokemonDescription.swift
//
//  Created by Paul Max on 6/23/20.
//  Copyright © 2020 CS50. All rights reserved.

import Foundation

//  MARK: - Get Pokémon Description (https://pokeapi.co/api/v2/pokemon-species/)

struct PokemonDescription: Codable {
    let flavor_text_entries: [FlavorTextEntries]
}
struct FlavorTextEntries: Codable {
    let flavor_text: String
    let language: Language
}
struct Language: Codable {
    let name: String
}
