//
//  Pokedex
//  PokemonModel.swift
//
//  Created by Paul Max on 6/23/20.
//  Copyright © 2020 CS50. All rights reserved.
//
//MARK: - PokemonViewController.swift - second view controller

import Foundation

struct PokemonResult: Codable {
    let id: Int
    let name: String
    let types: [PokemonTypeEntry]
    let sprites: PokemonImage
    let species: Species            // -> PokemonDescripton.swift
}
struct PokemonTypeEntry: Codable {
    let slot: Int
    let type: PokemonType
}
struct PokemonType: Codable {
    let name: String
}
struct Species: Codable {
    //let name: String
    let url: String
}
// Get Pokémon Image
struct PokemonImage: Codable {
    let front_default: String
}
