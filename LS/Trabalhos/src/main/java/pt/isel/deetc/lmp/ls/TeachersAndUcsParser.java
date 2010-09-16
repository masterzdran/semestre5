package pt.isel.deetc.lmp.ls;

import pt.isel.deetc.lmp.ls.domainModel.Teacher;

public class TeachersAndUcsParser {

	public Teacher parseTeacherLine(String teacherLine) {
		String[] teacherParts = teacherLine.split("\\|");
		return new Teacher(Integer.parseInt(teacherParts[0]), teacherParts[1], teacherParts[2]);
	}
}
