package fr.telecomlille.uvinfo2015;

import java.io.IOException;
import java.io.Reader;

/**
 * Extracteur de données CSV à partir d'un flux de caractères. Dans les fichiers
 * CSV exportés de openoffice calc, le séparateur est virgule, le délimiteur est
 * le guillemet. Si la cellule contient des virgules ou des guillemets, alors :
 * le texte exporté pour la cellule est encadré par des guillemets. Les
 * guillemets non délimiteurs sont doublés.
 */
public class CSVReader {

	/**
	 * Extrait d'une ligne d'un flux de caractères des champs séparés par des
	 * virgules. Les champs peuvent contenir un caractère de fin de ligne ou une
	 * virgule, dans ce cas les champs doivent être encadrés par des guillemets.
	 * Un caractère de fin de ligne non situé dans un champ ainsi encadré
	 * identifie une fin de ligne du flux et provoque la terminaison de cette
	 * méthode. Les champs ainsi encadrés peuvent aussi contenir des guillemets,
	 * pour ne pas le confondre avec une fin de champ encadré, un tel guillemet
	 * doit alors être doublé.
	 * 
	 * @param rdr
	 *            Le flux à partir duquel on lit.
	 * @return Le tableau de champs.
	 * @throws IOException
	 *             Si un erreur d'entrée-sortie se produit sur le flux.
	 */
	public String[] getLine(Reader rd) throws IOException {
		return null;
	}
}
