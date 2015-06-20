package fr.telecomlille.uvinfo2015;

import java.io.IOException;
import java.io.Reader;

/**
 * A class helping in reading lines from a Reader removing C-style comments.
 */
public class CommentStripper {
	// Symbols
	protected static final char SLASH = '/';
	protected static final char STAR = '*';
	protected static final char EOL = '\n';
	protected static final int EOF = -1;

	// states
	/** Out of Comment */
	protected static final int OC = 0;
	/** "Maybe Begin of Comment" state */
	protected static final int MBC = 1;
	/** "In Comment" state */
	protected static final int IC = 2;
	/** "Maybe End of Comment" state */
	protected static final int MEC = 3;
	
	/** automaton state */
	protected int state = OC;

	/** Whether there is a character read ahead */
	protected boolean ahead;
	/** ahead character if ahead is true */
	protected int tmp;
	/** Field string buffer */
	StringBuffer sb = new StringBuffer();

	/**
	 * Return a character from the reader dealing with different "end of line"
	 * styles; always return LF (line feed = \n) whatever be the style of
	 * "end of line" found in the stream.
	 * 
	 * @param rdr
	 *            The reader.
	 * @return The read character or EOF if end of stream found.
	 * @throws IOException
	 *             If an IO error occurs while reading the character.
	 */
	protected int read(Reader rdr) throws IOException {
		int c = ahead ? tmp : rdr.read();
		ahead = false;
		switch (c) {
		case '\r' :
			tmp = rdr.read();
			if (tmp == '\n')
				return EOL;
			c = EOL;
			ahead = true;
			break;
		case '\n' :
			tmp = rdr.read();
			if (tmp == '\r')
				return EOL;
			ahead = true;
		}
		return c;
	}

	/**
	 * Store c as a character in the string buffer.
	 * 
	 * @param c
	 *            The character code.
	 */
	protected void store(int c) {
		sb.append((char) c);
	}

	/**
	 * Get line from the Reader with C-style comments removed.
	 * 
	 * @param rdr
	 *            The Reader.
	 * @return The line.
	 * @throws IOException
	 *             If an IO error occurs while reading the line.
	 */
	public String getLine(Reader rd) throws IOException {
		while (true) {
			int c = read(rd);
			switch (state) {
			case OC :
				switch (c) {
				case SLASH :
					state = MBC;
					break;
				case EOL :
					return getEndedLine();
				case EOF :
					return getLine();
				default :
					store(c);
					break;
				}
				break;
			case MBC :
				switch (c) {
				case SLASH :
					store(SLASH);
					break;
				case STAR :
					state = IC;
					break;
				case EOL :
					store(SLASH);
					state = OC;
					return getEndedLine();
				case EOF :
					store(SLASH);
					state = OC;
					return getLine();
				}
				break;
			case IC :
				switch (c) {
				case STAR :
					state = MEC;
					break;
				case EOF :
					return getLine();
				}
				break;
			case MEC :
				switch (c) {
				case SLASH :
					state = OC;
					break;
				case EOF :
					return getLine();
				}
				break;
			}
		}
	}

	/**
	 * @return String buffer line.
	 */
	protected String getEndedLine() {
		String str = sb.toString();
		sb.setLength(0);
		return str;
	}

	/**
	 * @return String buffer line or null if empty.
	 */
	protected String getLine() {
		String str = sb.toString();
		sb.setLength(0);
		if (str.length() == 0)
			return null;
		return str;
	}
}
