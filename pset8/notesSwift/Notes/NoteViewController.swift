import UIKit

class NoteViewController: UIViewController {
    @IBOutlet var contentTextView: UITextView!
    
    @IBOutlet var barButton: UIBarButtonItem!
    
    var note: Note? = nil
    
    @IBAction func deleteNote() {
        let ac = UIAlertController(title: "Delete Note", message: "Are you sure you want to delete this note?", preferredStyle: .alert)
        ac.addAction(UIAlertAction(title: "OK", style: .default, handler: { action in
            if NoteManager.shared.deleteNote(note: self.note!) {
                self.navigationController?.popViewController(animated: true)
            }
        }))
        ac.addAction(UIAlertAction(title: "Cancel", style: .cancel))
        
        DispatchQueue.main.async {
            self.present(ac, animated: true, completion: nil)
        }
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        contentTextView.text = note!.content
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        
        note!.content = contentTextView.text
        NoteManager.shared.saveNote(note: note!)
    }
}
