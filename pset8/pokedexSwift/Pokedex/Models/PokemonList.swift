//
//  Pokedex
//  PokemonList.swift
//
//  Created by Paul Max on 6/23/20.
//  Copyright © 2020 CS50. All rights reserved.
//
//  MARK: - PokemonListViewController.swift - (https://pokeapi.co/api/v2/pokemon?limit=151)

import Foundation

struct PokemonListResults: Codable {
    let results: [PokemonListResult]
}
struct PokemonListResult: Codable {
    let name: String
    let url: String
}
