#!/usr/bin/env python

from sys import argv

if len(argv) < 1:
    print("expects input file")
    exit()

class RR:
    __slots__ = "name", "scene", "events", "checks", "exits"
    def __init__(self, name, scene):
        self.name = name
        self.scene = scene
        self.events = []
        self.checks = []
        self.exits = []

    def gen(self, code):
        return self.to_cpp(self.parse(code))

    def parse(self, code):
        if code[0] == "(" and code[-1] == ")":
            code = code[1:-1]
        stack = []
        ast = []
        balance = 0
        lastidx = 0
        for idx, ch in enumerate(code):
            if ch.isspace():
                if idx > lastidx:
                    ast.append(code[lastidx:idx])
                lastidx = idx+1
            elif ch == "(":
                stack.append(ast)
                ast = []
                lastidx = idx+1
            elif ch == ")":
                if idx > lastidx:
                    ast.append(code[lastidx:idx])
                subast = ast
                ast = stack.pop()
                ast.append(subast)
                lastidx = idx+1
        if len(code) > lastidx:
            ast.append(code[lastidx:])
        return ast

    def to_cpp(self, ast):
        result = []
        output = result.append
        if ast:
            if isinstance(ast, str):
                f = ast
                ast = [f]
            else:
                f = ast[0]
            if f in LOGIC:
                output(f"logic->{f}")
            elif f in logicFUNC:
                output(f"logic->{f}(")
                output(", ".join(map(self.to_cpp, ast[1:])))
                output(")")
            elif f in ctxFUNC:
                output(f"ctx->{f}(")
                output(", ".join(map(self.to_cpp, ast[1:])))
                output(")")
            elif f in FUNC:
                output(f"{f}(")
                output(", ".join(map(self.to_cpp, ast[1:])))
                output(")")
            elif f in binOP:
                output("(")
                output(binOP[f].join(map(self.to_cpp, ast[1:])))
                output(")")
            elif f == "not":
                output("!")
                output(self.to_cpp(ast[1]))
            elif f == "if":
                output("(")
                output(self.to_cpp(ast[1]))
                output(" ? ")
                output(self.to_cpp(ast[2]))
                output(" : ")
                output(self.to_cpp(ast[3]))
                output(")")
            elif f.startswith("RSK_"):
                output(f"ctx->GetOption(f{f})")
            elif f.startswith("RT_"):
                output(f"ctx->GetTrickOption(f{f})")
            elif f == "IsDungeonVanilla":
                output(f"ctx->GetDungeon(f{self.to_cpp(ast[1])})->IsVanilla()")
            elif f == "IsDungeonMQ":
                output(f"ctx->GetDungeon(f{self.to_cpp(ast[1])})->IsMQ()")
            elif f == "IsTrialSkipped":
                output(f"ctx->GetTrial(f{self.to_cpp(ast[1])})->IsSkipped()")
            elif f == "TriforcePiecesCollected":
                output("gSaveContext.ship.quest.data.randomizer.triforcePiecesCollected")
            elif f.startswith("HasProjectileAge"):
                output(f.replace("HasProjectileAge", "HasProjectileAge::"))
            elif f in RANDO:
                output(f"Rando::{f}")
            elif f == "Here":
                output("Here(f{self.name}, []{return f{self.to_cpp(ast[1])};})")
            elif f != "--":
                if len(ast) != 1:
                    print("expected atom, got tree", ast)
                elif f.isupper() or f.isdigit() or f in ("true", "false"):
                    output(f)
                else:
                    print("invalid atom", f)
        return "".join(result)

binOP = { "==": " == ", "and": " && ", "or": " || ", ">=": " >= ", "!=": " != ", ">": " > ", "<": " < ", "add": " + " }

LOGIC = {
    "IsChild",
    "IsAdult",
    "AtDay",
    "AtNight",
    "LoweredWaterInBotw",
    "BigPoes",
}

RANDO = {
    "DEKU_TREE",
    "DODONGOS_CAVERN",
    "JABU_JABUS_BELLY",
    "FOREST_TEMPLE",
    "FIRE_TEMPLE",
    "WATER_TEMPLE",
    "SPIRIT_TEMPLE",
    "SHADOW_TEMPLE",
    "BOTTOM_OF_THE_WELL",
    "ICE_CAVERN",
    "GERUDO_TRAINING_GROUND",
    "GANONS_CASTLE",
}

FUNC = {
    "MQSpiritSharedStatueRoom",
    "MQSpiritSharedBrokenWallRoom",
    "CanPlantBean",
    "BothAges",
    "ChildCanAccess",
    "AdultCanAccess",
    "HasAccessTo",
}

logicFUNC = {
    "BlueFire",
    "CanBreakMudWalls",
    "CanBuyCheck",
    "HasItem",
    "HasBossSoul",
    "HasFireSource",
    "HasFireSourceWithTorch",
    "CanUse",
    "CanPassEnemy",
    "CanKillEnemy",
    "CanGetEnemyDrop",
    "CanGetDekuBabaSticks",
    "CanGetDekuBabaNuts",
    "CanBreakPots",
    "CanBorrowMasks",
    "CanShield",
    "CanStandingShield",
    "CanReflectNuts",
    "CanStunDeku",
    "CanSpawnSoilSkull",
    "CanGetNightTimeGS",
    "CanOpenUnderwaterChest",
    "CanHitSwitch",
    "CanHitEyeTargets",
    "CanDetonateUprightBombFlower",
    "CanDetonateBombFlowers",
    "CanUseProjectile",
    "CanBreakLowerBeehives",
    "CanBreakUpperBeehives",
    "CallGossipFairy",
    "CallGossipFairyExceptSuns",
    "HasExplosives",
    "HasProjectile",
    "CanCutShrubs",
    "CanBreakCrates",
    "CanBreakSmallCrates",
    "StoneCount",
    "CanBuildRainbowBridge",
    "TradeQuestStep",
    "GetGSCount",
    "BlastOrSmash",
    "HookshotOrBoomerang",
    "TakeDamage",
    "CanAttack",
    "CanDamage",
    "CanUseSword",
    "CanJumpslash",
    "CanJumpslashExceptHammer",
    "HasBottle",
    "SmallKeys",
    "OcarinaButtons",
    "Hearts",
    "EffectiveHealth",
    "FireTimer",
    "WaterTimer",
    "MQWaterLevel",
    "CanTriggerLACS",
    "BombchusEnabled",
}

ctxFUNC = {
    "GetTrickOption",
    "GetOption",
}

RRs = []
active_rr = None
buf = ""
open_count = close_count = 0
for line in open(argv[1]):
    if line.startswith("def "):
        if open_count != close_count:
            print("error parsing:", name)
        defline = line.split()
        name = defline[1]
        active_rr = RR(name, defline[2])
        RRs.append(active_rr)
        buf = ""
        open_count = close_count = 0
        continue
    if line.startswith("--"):
        continue
    open_count += line.count('(')
    close_count += line.count(')')
    buf += line
    if open_count != close_count:
        continue
    if buf and buf.isspace(): continue
    try:
        thing, code = buf.split(None, 1)
        code = code.strip()
    except:
        print("failed to parse line", buf)
        continue
    if thing.startswith("RR_"):
        active_rr.exits.append((thing, code))
    elif thing.startswith("RC_"):
        active_rr.checks.append((thing, code))
    else:
        LOGIC.add(thing)
        active_rr.events.append((thing, code))
    buf = ""


result = []
output = result.append
for rr in RRs:
    output(f"areaTable[{rr.name}] = Region(\"...\", {rr.scene}, {{")
    if rr.events:
        output("\n")
        for name, code in rr.events:
            output(f"\tEventAccess(&logic->{name}, []{{return {rr.gen(code)};}}),\n")
    output("}, {")

    if rr.checks:
        output("\n")
        for name, code in rr.checks:
            output(f"\tLOCATION({name}, {rr.gen(code)}),\n")
    output("}, {")

    if rr.exits:
        output("\n")
        for name, code in rr.events:
            output(f"\tEntrance({name}, []{{return {rr.gen(code)};}}),\n")
    output("});\n")

print("".join(result))
