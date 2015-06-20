package fr.telecomlille.uvinfo2015;


import java.io.IOException;
import java.io.Reader;
import java.io.StringReader;

import fr.telecomlille.uvinfo2015.CSVReader;
import junit.framework.TestCase;

/**
 * Ce programme de test NE DOIT PAS �TRE MODIFIE. L'�valuation utilisera ce
 * programme de test non modifi�. Pour l'ex�uter, faire un Run As... JUnit Test.
 * On peut aussi mettre un point d'arr�t et faire Debug As... JUnit Test. Ce
 * programme de test est compos� de m�thodes de test commen�ant par public void
 * test... et sans param�tres.
 * 
 * NB: JUnit est une biblioth�que destin�e � faciliter la r�daction de tests
 * unitaires automatis�s. Chaque m�thode de test v�rifie la fa�on dont l'objet
 * test� a fonctionn� en utilisant des assertions qui indiquent dans leur nom le
 * comportement normal attendu de l'objet test� est au point. Par exemple,
 * assertNull(fieds) v�rifie que fields a la valeur null ce qui est le
 * comportement normal attendu de l'objet test�. De m�me, assertEquals(1,
 * fieds.length) v�rifie que fields.length a bien la valeur 1.
 * 
 * @author Christophe TOMBELLE
 */
public class CSVReaderTest extends TestCase {

	/**
	 * Quand le flux est ferm�, le comportement normal est de d�clencher une
	 * IOException.
	 */
	public void testClosedStream() {
		Reader rd = new StringReader(",");
		try {
			rd.close();
		} catch (IOException e) {
		}
		try {
			CSVReader csv = new CSVReader();
			csv.getLine(rd);
			fail("IOException should have been thrown");
		} catch (IOException e) {
			// normal expected exception
		} catch (Throwable t) {
			fail("IOException should be thrown");
		}
	}

	/**
	 * Quand le flux est vide, il n'y a pas de tableau.
	 */
	public void testEndOfStream() {
		Reader rd = new StringReader("");
		try {
			CSVReader csv = new CSVReader();
			String[] fieds = csv.getLine(rd);
			assertNull(fieds);
		} catch (IOException e) {
			fail();
		}
	}

	/**
	 * Les caract�res blancs {@link String#isWhiteSpace} avant et apr�s une
	 * donn�e sont ignor�s, si le flux ne contient que �a, il n'y a pas de
	 * tableau.
	 */
	public void testTrimEndOfStream() {
		Reader rd = new StringReader("   ");
		try {
			CSVReader csv = new CSVReader();
			String[] fieds = csv.getLine(rd);
			assertNull(fieds);
		} catch (IOException e) {
			fail();
		}
	}

	/**
	 * Cas simple avec un flux d'une seule ligne (la fin de flux joue le r�le de
	 * fin de ligne) et d'un seul champ.
	 */
	public void test1FieldEndOfStream() {
		Reader rd = new StringReader("a b c");
		try {
			CSVReader csv = new CSVReader();
			String[] fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(1, fieds.length);
			assertEquals("a b c", fieds[0]);
		} catch (IOException e) {
			fail();
		}
	}

	/**
	 * Cas simple avec un flux d'une seule ligne et d'un seul champ ; les
	 * caract�res blancs avant et apr�s les champs sont ignor�s
	 * {@link String#trim()}.
	 */
	public void testTrim1FieldEndOfStream() {
		Reader rd = new StringReader(" a b c  ");
		try {
			CSVReader csv = new CSVReader();
			String[] fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(1, fieds.length);
			assertEquals("a b c", fieds[0]);
		} catch (IOException e) {
			fail();
		}
	}

	/**
	 * Cas d'un flux avec un seule ligne sans champs.
	 */
	public void test1EmptyField() {
		Reader rd = new StringReader("\n");
		try {
			CSVReader csv = new CSVReader();
			String[] fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(1, fieds.length);
			assertEquals("", fieds[0]);
			fieds = csv.getLine(rd);
			assertNull(fieds);
		} catch (IOException e) {
			fail();
		}
	}

	/**
	 * Cas d'un flux avec un seule ligne sans champs mais avec des caract�res
	 * blancs � �liminer.
	 */
	public void testTrim1EmptyField() {
		Reader rd = new StringReader("   \n   ");
		try {
			CSVReader csv = new CSVReader();
			String[] fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(1, fieds.length);
			assertEquals("", fieds[0]);
			fieds = csv.getLine(rd);
			assertNull(fieds);
		} catch (IOException e) {
			fail();
		}
	}

	/**
	 * Cas d'un flux d'une ligne � 2 champs vides et un vrai caract�re de fin de
	 * ligne.
	 */
	public void test2EmptyFields() {
		Reader rd = new StringReader(",\n");
		try {
			CSVReader csv = new CSVReader();
			String[] fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(2, fieds.length);
			assertEquals("", fieds[0]);
			assertEquals("", fieds[1]);
		} catch (IOException e) {
			fail();
		}
	}

	/**
	 * Cas d'un flux d'une ligne � 2 champs ne contenant que des blancs et un
	 * vrai caract�re de fin de ligne.
	 */
	public void testTrim2EmptyFields() {
		Reader rd = new StringReader("  ,  \n");
		try {
			CSVReader csv = new CSVReader();
			String[] fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(2, fieds.length);
			assertEquals("", fieds[0]);
			assertEquals("", fieds[1]);
		} catch (IOException e) {
			fail();
		}
	}

	/**
	 * Cas simple avec un flux d'une seule ligne (avec un vrai caract�re fin de
	 * ligne) et un seul champ.
	 */
	public void test1Field() {
		Reader rd = new StringReader("a b c\n");
		try {
			CSVReader csv = new CSVReader();
			String[] fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(1, fieds.length);
			assertEquals("a b c", fieds[0]);
			fieds = csv.getLine(rd);
			assertNull(fieds);
		} catch (IOException e) {
			fail();
		}
	}

	/**
	 * Cas d'un flux d'une seule ligne (avec un vrai caract�re fin de ligne) et
	 * un seul champ mais avec des blancs d'encadrement.
	 */
	public void testTrim1Field() {
		Reader rd = new StringReader("  a b c  \n");
		try {
			CSVReader csv = new CSVReader();
			String[] fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(1, fieds.length);
			assertEquals("a b c", fieds[0]);
		} catch (IOException e) {
			fail();
		}
	}

	/**
	 * Cas d'un flux d'une seule ligne (avec un vrai caract�re fin de
	 * ligne) � 2 champs.
	 */
	public void test2Fields() {
		Reader rd = new StringReader("a b c,d e f\n");
		try {
			CSVReader csv = new CSVReader();
			String[] fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(2, fieds.length);
			assertEquals("a b c", fieds[0]);
			assertEquals("d e f", fieds[1]);
		} catch (IOException e) {
			fail();
		}
	}

	/**
	 * Cas d'un flux d'une seule ligne (avec un vrai caract�re fin de
	 * ligne) � 2 champs avec blancs d'encadrement.
	 */
	public void testTrim2Fields() {
		Reader rd = new StringReader("  a b c  ,  d e f \n");
		try {
			CSVReader csv = new CSVReader();
			String[] fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(2, fieds.length);
			assertEquals("a b c", fieds[0]);
			assertEquals("d e f", fieds[1]);
		} catch (IOException e) {
			fail();
		}
	}

	/**
	 * Cas d'un flux d'une seule ligne (avec un vrai caract�re fin de
	 * ligne) et un seul champ entre guillemets et des blancs de fin.
	 */
	public void test1QuotedField() {
		Reader rd = new StringReader("\"a b c  \"\n");
		try {
			CSVReader csv = new CSVReader();
			String[] fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(1, fieds.length);
			assertEquals("a b c", fieds[0]);
		} catch (IOException e) {
			fail();
		}
	}

	/**
	 * Cas d'un flux d'une seule ligne (avec un vrai caract�re fin de ligne) et
	 * un seul champ entre guillemets contenant une fin de ligne � ignorer car
	 * situ�e entre les guillemets ; blancs de fin.
	 */
	public void test1QuotedEOLField() {
		Reader rd = new StringReader("\"a \nb c  \"\n");
		try {
			CSVReader csv = new CSVReader();
			String[] fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(1, fieds.length);
			assertEquals("a b c", fieds[0]);
		} catch (IOException e) {
			fail();
		}
	}

	/**
	 * Cas d'un flux d'une seule ligne (avec un vrai caract�re fin de ligne) et
	 * un seul champ entre guillemets contenant a) une fin de ligne � ignorer
	 * car situ�e entre les guillemets b) un guillemet (doubl� pour ne pas le
	 * confondre avec le guillemet de fin de champ) c) des blancs de fin.
	 */
	public void test1ComplexQuotedField() {
		Reader rd = new StringReader("\"a \n\"\"b\"\" c  \"\n");
		try {
			CSVReader csv = new CSVReader();
			String[] fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(1, fieds.length);
			assertEquals("a \"b\" c", fieds[0]);
		} catch (IOException e) {
			fail();
		}
	}

	/**
	 * Cas d'un flux � 2 lignes d'un seul champ (la fin de flux termine la 2�me
	 * ligne).
	 */
	public void test1FieldPerLine() {
		Reader rd = new StringReader("a b c\nd e f");
		try {
			CSVReader csv = new CSVReader();
			String[] fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(1, fieds.length);
			assertEquals("a b c", fieds[0]);
			fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(1, fieds.length);
			assertEquals("d e f", fieds[0]);
		} catch (IOException e) {
			fail();
		}
	}

	/**
	 * Cas d'un flux � 2 lignes � 2 champs (la fin de flux termine la 2�me
	 * ligne).
	 */
	public void test2FieldsPerLine() {
		Reader rd = new StringReader("a b c,d e f\n"
				+ "ghi,jkl");
		try {
			CSVReader csv = new CSVReader();
			String[] fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(2, fieds.length);
			assertEquals("a b c", fieds[0]);
			assertEquals("d e f", fieds[1]);
			fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(2, fieds.length);
			assertEquals("ghi", fieds[0]);
			assertEquals("jkl", fieds[1]);
		} catch (IOException e) {
			fail();
		}
	}

	/**
	 * Cas d'un flux � 2 lignes � 2 champs entre guillemets et des blancs en
	 * dehors des guillemets (syntaxe normalement ill�gale mais qu'on ignore
	 * silencieusement par souci de robustesse).
	 */
	public void test2QuotedFieldsPerLine() {
		Reader rd = new StringReader(
			"   \"a b c \"   ,   \"d e f\"   \n"
			+ "   \"ghi\"   ,   \"jkl\"   ");
		try {
			CSVReader csv = new CSVReader();
			String[] fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(2, fieds.length);
			assertEquals("a b c", fieds[0]);
			assertEquals("d e f", fieds[1]);
			fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(2, fieds.length);
			assertEquals("ghi", fieds[0]);
			assertEquals("jkl", fieds[1]);
		} catch (IOException e) {
			fail();
		}
	}

	/**
	 * Cas d'un flux � 2 lignes � 2 champs entre guillemets (complexes pour
	 * certains car contenant fin de ligne ou guillemet non d�limiteur) et des
	 * blancs en dehors des guillemets (syntaxe normalement ill�gale mais qu'on
	 * ignore silencieusement par souci de robustesse).
	 */
	public void test2ComplexQuotedFieldsPerLine() {
		Reader rd = new StringReader("  \"a \nb c\"  ,  \"d e\n f\"  \n"
				+ "  \" g\nhi \"  ,  \"j\n\"\"kl\"  ");
		try {
			CSVReader csv = new CSVReader();
			String[] fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(2, fieds.length);
			assertEquals("a b c", fieds[0]);
			assertEquals("d e f", fieds[1]);
			fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(2, fieds.length);
			assertEquals("ghi", fieds[0]);
			assertEquals("j\"kl", fieds[1]);
		} catch (IOException e) {
			fail();
		}
	}

	/**
	 * Les caract�res non blancs avant et apr�s des cha�nes des guillemets
	 * correspondent � une syntaxe ill�gale. On choisit de les ignorer
	 * silencieusement par souci de robustesse.
	 */
	public void testRobustness() {
		Reader rd = new StringReader("ignored\"a \nb c\"ignored,d e f\n"
				+ "ignored\" g\nhi \"ignored,ignored\"j\n\"\"kl\"ignored");
		try {
			CSVReader csv = new CSVReader();
			String[] fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(2, fieds.length);
			assertEquals("a b c", fieds[0]);
			assertEquals("d e f", fieds[1]);
			fieds = csv.getLine(rd);
			assertNotNull(fieds);
			assertEquals(2, fieds.length);
			assertEquals("ghi", fieds[0]);
			assertEquals("j\"kl", fieds[1]);
		} catch (IOException e) {
			fail();
		}
	}
}
