import math

class Display(object):

	"""
	A display is a structure with a dictionary of points, having a character
	value associated to them.
	"""

	def __init__(self):
		self._screen = {}

		self.empty_char = " "
		self.fill_char = "@"

	def _update_minmax(self, x, y, adding = True):

		"""
		Updates self._min_y, self._max_y, self._min_x and self._max_x values.
		"""

		if not hasattr(self, "_min_y"):
			self._min_y = y
			self._max_y = y
			self._min_x = x
			self._max_x = x

		elif adding:
			self._min_y = y if y < self._min_y else self._min_y
			self._max_y = y if y > self._max_y else self._max_y
			self._min_x = x if x < self._min_x else self._min_x
			self._max_x = x if x > self._max_x else self._max_x

		else:
			ylist = [p[1] for p in self._screen.keys()]
			xlist = [p[0] for p in self._screen.keys()]

			self._min_y = min(ylist)
			self._max_y = max(ylist)
			self._min_x = min(xlist)
			self._max_x = max(xlist)

	def show(self):

		"""
		Print the content of the display onscreen.
		"""

		assert hasattr(self, "_screen"), \
			"This method must be called from an instance."

		buf = ""

		for y in xrange(self._max_y, self._min_y - 1, -1):

			for x in xrange(self._min_x, self._max_x + 1):
				buf += self._screen[(x, y)] if (x, y) in self._screen else \
					self.empty_char

			buf += "\n"

		print buf[:-1]

	def showregion(self, x1, y1, x2, y2):

		"""
		Prints the content of the display in a region determined by two points.
		"""

		assert hasattr(self, "_screen"), \
			"This method must be called from an instance."

		assert type(x1) is int and type(y1) is int and \
			type(x2) is int and type(y2) is int, \
			"Coordinates must be given in (int, int) form."

		if y1 > y2:
			y1, y2 = y2, y1
		if x1 > x2:
			x1, x2 = x2, x1

		buf = ""

		for y in xrange(y2, y1 - 1, -1):

			for x in xrange(x1, x2 + 1):
				buf += self._screen[(x, y)] if (x, y) in self._screen else \
					self.empty_char

			buf += "\n"

		print buf[:-1]

	def put(self, x, y, c):

		"""
		Sets a given (x, y) position to a given character c.
		"""

		assert type(x) is int and type(y) is int, \
			"Coordinates must be given in (int, int) form."
		assert type(c) is str and len(c) == 1, \
			"You can only store characters in given positions."

		self._screen[(x, y)] = c
		self._update_minmax(x, y)

	def fill(self, x, y):

		"""
		Sets a given (x, y) position to this instance's fill_char attribute.
		"""

		self.put(x, y, self.fill_char)
		self._update_minmax(x, y)

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

		self._update_minmax(x, y, False)

	def get(self, x, y):

		"""
		Returns the value of a pixel in given position (x, y).
		"""

		assert type(x) is int and type(y) is int, \
			"Coordinates must be given in (int, int) form."

		try:
			return self._screen[(x, y)]
		except KeyError:
			return self.empty_char


class Pencil(object):

	"""
	Used to draw simple things on a display object.
	"""

	def __init__(self, display):

		assert isinstance(display, Display), \
			"A pencil is to be associated with a display."

		self._target = display
		self.fill_char = display.fill_char

	def drawrect(self, x1, y1, x2, y2):

		"""
		Draws a rectangle using given coordinates as opposite vertices.
		"""

		assert type(x1) is int and type(y1) is int and type(x2) is int and \
			type(y2) is int, "Coordinates must be given in (int, int) form."

		if x1 > x2:
			x1, x2 = x2, x1
		if y1 > y2:
			y1, y2 = y2, y1

		for x in xrange(x1, x2):
			for y in xrange(y1, y2):
				self._target.put(x, y, self.fill_char)

	def drawline(self, x1, y1, x2, y2):

		"""
		Draws a line given two points.
		"""

		assert type(x1) is int and type(y1) is int and type(x2) is int and \
			type(y2) is int, "Coordinates must be given in (int, int) form."

		if x1 == x2:
			if y1 > y2:
				y1, y2 = y2, y1

			for y in xrange(y1, y2 + 1):
				self._target.put(x1, y, self.fill_char)

			return
		elif y1 == y2:
			if x1 > x2:
				x1, x2 = x2, x1

			for x in xrange(x1, x2 + 1):
				self._target.put(x, y1, self.fill_char)

			return

		m = (y2 - y1)/(x2 - x1)
		n = y1 - m*x1

		if m > 1:
			self._drawline_mgt1(y1, y2, m, n)
		elif m < 1:
			self._drawline_mlt1(x1, x2, m, n)
		else:
			if x1 > x2:
				x1, x2 = x2, x1

			for x in xrange(x1, x2 + 1):
				self._target.put(x, x + n, self.fill_char)

	def _drawline_mlt1(self, x1, x2, m, n):

		"""
		Rasterises a straight line given it has an angular coefficient lower
		than 1.

		It will walk each value of x, filling y with a Bresenham-like approach
		to the real value of y in the correspondent point on the straight line.
		"""

		if x1 > x2:
			x1, x2 = x2, x1

		for x in xrange(x1, x2 + 1):
			real_y  = m*x + n
			floor_y = int(math.floor(real_y))
			ceil_y  = int(math.ceil(real_y))

			if abs(floor_y - real_y) < abs(ceil_y - real_y):
				self._target.put(x, floor_y, self.fill_char)
			else:
				self._target.put(x, ceil_y, self.fill_char)

	def _drawline_mgt1(self, y1, y2, m, n):

		"""
		Rasterises a straight line given it has an angular coefficient greater
		than 1.

		It will walk each value of y, filling x with a Bresenham-like approach
		to the real value of x in the correspondent point on the straight line.
		"""

		if y1 > y2:
			y1, y2 = y2, y1

		for y in xrange(y1, y2 + 1):
			real_x = (y - n)/m
			floor_x = int(math.floor(real_x))
			ceil_x = int(math.ceil(real_x))

			if abs(floor_x - real_x) < abs(ceil_x - real_x):
				self._target.put(floor_x, y, self.fill_char)
			else:
				self._target.put(ceil_x, y, self.fill_char)

