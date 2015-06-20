package fr.telecomlille.uvinfo2015;


import java.io.IOException;
import java.io.Reader;
import java.io.StringReader;

import fr.telecomlille.uvinfo2015.CSVReader;
import junit.framework.TestCase;

/**
 * Ce programme de test NE DOIT PAS ÊTRE MODIFIE. L'évaluation utilisera ce
 * programme de test non modifié. Pour l'exéuter, faire un Run As... JUnit Test.
 * On peut aussi mettre un point d'arrêt et faire Debug As... JUnit Test. Ce
 * programme de test est composé de méthodes de test commençant par public void
 * test... et sans paramètres.
 * 
 * NB: JUnit est une bibliothèque destinée à faciliter la rédaction de tests
 * unitaires automatisés. Chaque méthode de test vérifie la façon dont l'objet
 * testé a fonctionné en utilisant des assertions qui indiquent dans leur nom le
 * comportement normal attendu de l'objet testé est au point. Par exemple,
 * assertNull(fieds) vérifie que fields a la valeur null ce qui est le
 * comportement normal attendu de l'objet testé. De même, assertEquals(1,
 * fieds.length) vérifie que fields.length a bien la valeur 1.
 * 
 * @author Christophe TOMBELLE
 */
public class CSVReaderTest extends TestCase {

	/**
	 * Quand le flux est fermé, le comportement normal est de déclencher une
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
	 * Les caractères blancs {@link String#isWhiteSpace} avant et après une
	 * donnée sont ignorés, si le flux ne contient que ça, il n'y a pas de
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
	 * Cas simple avec un flux d'une seule ligne (la fin de flux joue le rôle de
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
	 * caractères blancs avant et après les champs sont ignorés
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
	 * Cas d'un flux avec un seule ligne sans champs mais avec des caractères
	 * blancs à éliminer.
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
	 * Cas d'un flux d'une ligne à 2 champs vides et un vrai caractère de fin de
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
	 * Cas d'un flux d'une ligne à 2 champs ne contenant que des blancs et un
	 * vrai caractère de fin de ligne.
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
	 * Cas simple avec un flux d'une seule ligne (avec un vrai caractère fin de
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
	 * Cas d'un flux d'une seule ligne (avec un vrai caractère fin de ligne) et
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
	 * Cas d'un flux d'une seule ligne (avec un vrai caractère fin de
	 * ligne) à 2 champs.
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
	 * Cas d'un flux d'une seule ligne (avec un vrai caractère fin de
	 * ligne) à 2 champs avec blancs d'encadrement.
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
	 * Cas d'un flux d'une seule ligne (avec un vrai caractère fin de
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
	 * Cas d'un flux d'une seule ligne (avec un vrai caractère fin de ligne) et
	 * un seul champ entre guillemets contenant une fin de ligne à ignorer car
	 * située entre les guillemets ; blancs de fin.
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
	 * Cas d'un flux d'une seule ligne (avec un vrai caractère fin de ligne) et
	 * un seul champ entre guillemets contenant a) une fin de ligne à ignorer
	 * car située entre les guillemets b) un guillemet (doublé pour ne pas le
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
	 * Cas d'un flux à 2 lignes d'un seul champ (la fin de flux termine la 2ème
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
	 * Cas d'un flux à 2 lignes à 2 champs (la fin de flux termine la 2ème
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
	 * Cas d'un flux à 2 lignes à 2 champs entre guillemets et des blancs en
	 * dehors des guillemets (syntaxe normalement illégale mais qu'on ignore
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
	 * Cas d'un flux à 2 lignes à 2 champs entre guillemets (complexes pour
	 * certains car contenant fin de ligne ou guillemet non délimiteur) et des
	 * blancs en dehors des guillemets (syntaxe normalement illégale mais qu'on
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
	 * Les caractères non blancs avant et après des chaînes des guillemets
	 * correspondent à une syntaxe illégale. On choisit de les ignorer
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
