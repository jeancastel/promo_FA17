package fr.telecomlille.uvinfo2015;

import java.io.IOException;
import java.io.Reader;
import java.io.StringReader;

import fr.telecomlille.uvinfo2015.CommentStripper;
import junit.framework.TestCase;

public class CommentStripperTest extends TestCase {
	public void testReadCRLF() {
		Reader rd = new StringReader("\r\na");
		try {
			CommentStripper cs = new CommentStripper();
			int c = cs.read(rd);
			assertEquals(CommentStripper.EOL, c);
			c = cs.read(rd);
			assertEquals('a', c);
			c = cs.read(rd);
			assertEquals(CommentStripper.EOF, c);
		} catch (IOException e) {
			fail();
		}
	}

	public void testReadLFCR() {
		Reader rd = new StringReader("\n\ra");
		try {
			CommentStripper cs = new CommentStripper();
			int c = cs.read(rd);
			assertEquals(CommentStripper.EOL, c);
			c = cs.read(rd);
			assertEquals('a', c);
			c = cs.read(rd);
			assertEquals(CommentStripper.EOF, c);
		} catch (IOException e) {
			fail();
		}
	}

	public void testReadCRCR() {
		Reader rd = new StringReader("\r\ra");
		try {
			CommentStripper cs = new CommentStripper();
			int c = cs.read(rd);
			assertEquals(CommentStripper.EOL, c);
			c = cs.read(rd);
			assertEquals(CommentStripper.EOL, c);
			c = cs.read(rd);
			assertEquals('a', c);
			c = cs.read(rd);
			assertEquals(CommentStripper.EOF, c);
		} catch (IOException e) {
			fail();
		}
	}

	public void testReadLFLF() {
		Reader rd = new StringReader("\n\na");
		try {
			CommentStripper cs = new CommentStripper();
			int c = cs.read(rd);
			assertEquals(CommentStripper.EOL, c);
			c = cs.read(rd);
			assertEquals(CommentStripper.EOL, c);
			c = cs.read(rd);
			assertEquals('a', c);
			c = cs.read(rd);
			assertEquals(CommentStripper.EOF, c);
		} catch (IOException e) {
			fail();
		}
	}

	public void testReadCROther() {
		Reader rd = new StringReader("\ra");
		try {
			CommentStripper cs = new CommentStripper();
			int c = cs.read(rd);
			assertEquals(CommentStripper.EOL, c);
			c = cs.read(rd);
			assertEquals('a', c);
			c = cs.read(rd);
			assertEquals(CommentStripper.EOF, c);
		} catch (IOException e) {
			fail();
		}
	}

	public void testReadLFOther() {
		Reader rd = new StringReader("\na");
		try {
			CommentStripper cs = new CommentStripper();
			int c = cs.read(rd);
			assertEquals(CommentStripper.EOL, c);
			c = cs.read(rd);
			assertEquals('a', c);
			c = cs.read(rd);
			assertEquals(CommentStripper.EOF, c);
		} catch (IOException e) {
			fail();
		}
	}

	public void testCommentOnly() {
		Reader rd = new StringReader("/**/");
		try {
			CommentStripper cs = new CommentStripper();
			String str = cs.getLine(rd);
			assertEquals(null, str);
		} catch (IOException e) {
			fail();
		}
	}

	public void testEOLInComment() {
		Reader rd = new StringReader("/*\r\r\n\n\r\n\n\r*/");
		try {
			CommentStripper cs = new CommentStripper();
			String str = cs.getLine(rd);
			assertEquals(null, str);
		} catch (IOException e) {
			fail();
		}
	}

	public void testOtherInComment() {
		Reader rd = new StringReader("/*abc*/");
		try {
			CommentStripper cs = new CommentStripper();
			String str = cs.getLine(rd);
			assertEquals(null, str);
		} catch (IOException e) {
			fail();
		}
	}

	public void testUnclosedComment() {
		Reader rd = new StringReader("abc/*/abc");
		try {
			CommentStripper cs = new CommentStripper();
			String str = cs.getLine(rd);
			assertEquals("abc", str);
			str = cs.getLine(rd);
			assertEquals(null, str);
		} catch (IOException e) {
			fail();
		}
	}

	public void testBeforeCommentAfter() {
		Reader rd = new StringReader("abc/* *** def\r\nghi *** */jkl");
		try {
			CommentStripper cs = new CommentStripper();
			String str = cs.getLine(rd);
			assertEquals("abcjkl", str);
			str = cs.getLine(rd);
			assertEquals(null, str);
		} catch (IOException e) {
			fail();
		}
	}

	public void testCommentNewLineComment() {
		Reader rd = new StringReader("/* commented out */\n/* commented out */");
		try {
			CommentStripper cs = new CommentStripper();
			String str = cs.getLine(rd);
			assertEquals("", str);
			str = cs.getLine(rd);
			assertEquals(null, str);
		} catch (IOException e) {
			fail();
		}
	}

	public void testTwoLines() {
		Reader rd = new StringReader("abc/* commented out */def\nghi/* commented out */jkl");
		try {
			CommentStripper cs = new CommentStripper();
			String str = cs.getLine(rd);
			assertEquals("abcdef", str);
			str = cs.getLine(rd);
			assertEquals("ghijkl", str);
			str = cs.getLine(rd);
			assertEquals(null, str);
		} catch (IOException e) {
			fail();
		}
	}

	public void testEndStreamOnSlash() {
		Reader rd = new StringReader("abc/");
		try {
			CommentStripper cs = new CommentStripper();
			String str = cs.getLine(rd);
			assertEquals("abc/", str);
			str = cs.getLine(rd);
			assertEquals(null, str);
		} catch (IOException e) {
			fail();
		}
	}

	public void testEndStreamOnStar() {
		Reader rd = new StringReader("abc/**");
		try {
			CommentStripper cs = new CommentStripper();
			String str = cs.getLine(rd);
			assertEquals("abc", str);
			str = cs.getLine(rd);
			assertEquals(null, str);
		} catch (IOException e) {
			fail();
		}
	}

	public void testEndStreamOnStarEOL() {
		Reader rd = new StringReader("abc/**\n");
		try {
			CommentStripper cs = new CommentStripper();
			String str = cs.getLine(rd);
			assertEquals("abc", str);
			str = cs.getLine(rd);
			assertEquals(null, str);
		} catch (IOException e) {
			fail();
		}
	}

	public void testFalseBeginOfComment() {
		Reader rd = new StringReader("abc/\n");
		try {
			CommentStripper cs = new CommentStripper();
			String str = cs.getLine(rd);
			assertEquals("abc/", str);
			str = cs.getLine(rd);
			assertEquals(null, str);
		} catch (IOException e) {
			fail();
		}
	}

	public void testSlashInComment() {
		Reader rd = new StringReader("abc/*///*/def");
		try {
			CommentStripper cs = new CommentStripper();
			String str = cs.getLine(rd);
			assertEquals("abcdef", str);
			str = cs.getLine(rd);
			assertEquals(null, str);
		} catch (IOException e) {
			fail();
		}
	}
}
