import UIKit

class PokemonListViewController: UITableViewController, UISearchBarDelegate {
    
    var pokemon: [PokemonListResult] = []               
    var currentPokemonsArray: [PokemonListResult] = []  
    
    @IBOutlet var searchBar: UISearchBar!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        searchBar.delegate = self
        
        guard let url = URL(string: "https://pokeapi.co/api/v2/pokemon?limit=151") else { return }
        URLSession.shared.dataTask(with: url) { (data, response, error) in
            guard let data = data else { return }
            
            do {
                let entries = try JSONDecoder().decode(PokemonListResults.self, from: data)
                self.pokemon = entries.results
                
                // save data in array
                self.currentPokemonsArray = self.pokemon
                DispatchQueue.main.async { self.tableView.reloadData() }
            } catch let error { print(error) }
        }.resume()
    }
    
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return currentPokemonsArray.count
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "PokemonCell", for: indexPath)
        cell.textLabel?.text = capitalize(text: currentPokemonsArray[indexPath.row].name)
        return cell
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "ShowPokemonSegue",
            let destination = segue.destination as? PokemonViewController,
            let index = tableView.indexPathForSelectedRow?.row {
            destination.url = currentPokemonsArray[index].url
            destination.name = capitalize(text: currentPokemonsArray[index].name)
        }
    }
    
    func capitalize(text: String) -> String {
        return text.prefix(1).uppercased() + text.dropFirst()
    }
    
    func searchBar(_ searchBar: UISearchBar, textDidChange searchText: String) {
        guard !searchText.isEmpty else {
            currentPokemonsArray = pokemon
            tableView.reloadData()
            return
        }
        currentPokemonsArray = pokemon.filter({ pokemon -> Bool in
            return pokemon.name.lowercased().contains(searchText.lowercased())
        })
        tableView.reloadData()
    }
}
