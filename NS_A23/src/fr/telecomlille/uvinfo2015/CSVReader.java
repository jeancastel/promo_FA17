package fr.telecomlille.uvinfo2015;

import java.io.IOException;
import java.io.Reader;

/**
 * Extracteur de donn�es CSV � partir d'un flux de caract�res. Dans les fichiers
 * CSV export�s de openoffice calc, le s�parateur est virgule, le d�limiteur est
 * le guillemet. Si la cellule contient des virgules ou des guillemets, alors :
 * le texte export� pour la cellule est encadr� par des guillemets. Les
 * guillemets non d�limiteurs sont doubl�s.
 */
public class CSVReader {

	/**
	 * Extrait d'une ligne d'un flux de caract�res des champs s�par�s par des
	 * virgules. Les champs peuvent contenir un caract�re de fin de ligne ou une
	 * virgule, dans ce cas les champs doivent �tre encadr�s par des guillemets.
	 * Un caract�re de fin de ligne non situ� dans un champ ainsi encadr�
	 * identifie une fin de ligne du flux et provoque la terminaison de cette
	 * m�thode. Les champs ainsi encadr�s peuvent aussi contenir des guillemets,
	 * pour ne pas le confondre avec une fin de champ encadr�, un tel guillemet
	 * doit alors �tre doubl�.
	 * 
	 * @param rdr
	 *            Le flux � partir duquel on lit.
	 * @return Le tableau de champs.
	 * @throws IOException
	 *             Si un erreur d'entr�e-sortie se produit sur le flux.
	 */
	public String[] getLine(Reader rd) throws IOException {
		return null;
	}
}
