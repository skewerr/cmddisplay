class Display(object):

	"""
	A display is a structure with a dictionary of points, having a character
	value associated to them.
	"""

	def __init__(self):
		self._screen = {}
		self._width = 0
		self._height = 0

		self.empty_char = " "
		self.fill_char = "@"

	def show(self):

		"""
		Print the content of the display onscreen.
		"""

		assert hasattr(self, "_screen"), \
		"This method must be called from an instance."

		for y in xrange(self._height):
			line = [self._screen[(x, y)] if (x, y) in self._screen else \
				self.empty_char for x in xrange(self._width)]

			print line

	def set(self, x, y, c):

		"""
		Sets a given (x, y) position to a given character c.
		"""

		assert type(x) is int and type(y) is int, \
			"Coordinates must be given in (int, int) form."
		assert type(c) is str and len(c) == 1, \
			"You can only store characters in given positions."

		self._screen[(x, y)] = c

	def fill(self, x, y):

		"""
		Sets a given (x, y) position to this instance's fill_char attribute.
		"""

		self.set(x, y, self.fill_char)

	def empty(self, x, y):

		"""
		Removes a given (x, y) tuple from the screen dictionary.
		"""

		assert type(x) is int and type(y) is int, \
			"Coordinates must be given in (int, int) form."

		try:
			del self._screen[(x, y)]
		except KeyError:
			pass

